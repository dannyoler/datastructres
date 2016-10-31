#include <stdio.h>
#include <stdlib.h>

/* Simple matrix multiplication example.
 */

struct matrix {
	int *base; /* Base address. */
	int n_rows;
	int n_cols;
};

int matrix_init(struct matrix *m, int n_rows, int n_cols)
{
	m->base = calloc(n_rows * n_cols, sizeof(int));
	if (!m->base) {
		perror("calloc");
		abort();
	}

	m->n_rows = n_rows;
	m->n_cols = n_cols;

	return 0;
}

void matrix_destroy(struct matrix *a)
{
	if (a != NULL) {
		free(a->base);
		a->base = NULL;
	}
}

int matrix_from_random(struct matrix *a, int n_rows, int n_cols)
{
	int i, j;
	matrix_init(a, n_rows, n_cols);

	for (i=0; i<n_rows; i++) {
		for (j=0; j<n_cols; j++) {
			a->base[i * n_cols + j] = random() % 10;
		}
	}

	return 0;
}


int matrix_from_file(struct matrix *a, const char *path)
{
	int n_rows, n_cols;
	int i, j;

	/* Fill matrix from a file */
	FILE *fp = fopen(path, "rb");
	if (!fp) {
		perror("fopen");
		return -1;
	}

	if (fscanf(fp, "%d %d", &n_rows, &n_cols) != 2) {
		fprintf(stderr, "Error reading matrix from %s: malformed input\n", path);
		return -1;
	}

	matrix_init(a, n_rows, n_cols);

	/* Insert in your code here to read from the file and fill in
	 * the new matrix.
	 *////////////////////////////////////////////////////////////
	 for( i=0; i<n_rows; i++ ) {
	 	for ( j=0; j<n_cols; j++ ) {
	 		fscanf( fp, "%d\n", &(a->base[ i * n_cols + j ]) );
	 	}
	 }
	 

	fclose(fp);
	return 0;
}

void matrix_print(const struct matrix *a)
{
	int i, j;
	int n_rows = a->n_rows;
	int n_cols = a->n_cols;

	for (i=0; i<n_rows; i++) {
		for (j=0; j<n_cols; j++) {
			printf("%5d ", a->base[i * n_cols + j]);
		}
		printf("\n");
	}
}

int matrix_multiply(struct matrix *c, const struct matrix *a, const struct matrix *b)
{
	/* A is m * n x n * p = m * p */

	const int *A = a->base;
	const int *B = b->base;
	int *C = c->base;

	int m = a->n_rows;
	int n = a->n_cols;
	int p = c->n_cols;

	int i, j, k;

	if (c->n_rows != a->n_rows) {
		return -1;
	}

	if (c->n_cols != b->n_cols) {
		return -1;
	}

	if (a->n_cols != b->n_rows) {
		return -1;
	}

	/* Initialize the output matrix. */
	for (i=0; i<m; i++) {
		for (j=0; j<p; j++) {
			C[i * p + j] = 0;
		}
	}

	/* Fill in your code here to compute all the entries of matrix c 
	/////////////////////////////////////////////////////////////////*/
	int bc = b->n_cols, sum;
	for (i=0; i<m; i++) {
		for (j=0; j<p; j++) {
			sum = 0;
			for ( k=0; k<n; k++ ) {
				sum += (A[ i * n + k ])*(B[ k * bc + j ]);
			}
			C[i * p + j] = sum;
		}
	}

	return 0;
}




int main(int argc, char *argv[])
{
	int print_matrix = 1;
	struct matrix a, b, c;

	if (argc < 3) {
		fprintf(stderr, "Usage : matrix file_a file_b\n");
		fprintf(stderr, "   or : matrix m n p\n");
		exit(1);
	}

	if (argc > 3) {
		int m, n, p;
		m = strtol(argv[1], NULL, 10);
		n = strtol(argv[2], NULL, 10);
		p = strtol(argv[3], NULL, 10);

		print_matrix = 1;
		if (argc > 4) {
			print_matrix = strtol(argv[4], NULL, 10);
		}

		matrix_from_random(&a, m, n);
		matrix_from_random(&b, n, p);
	}
	else {
		if (matrix_from_file(&a, argv[1])) {
			exit(1);
		}


		if (matrix_from_file(&b, argv[2])) {
			exit(1);
		}
	}

	if (print_matrix) {
		printf("a is a %d by %d:\n", a.n_rows, a.n_cols);
		matrix_print(&a);
		printf("\n");

		printf("b is a %d by %d:\n", b.n_rows, b.n_cols);
		matrix_print(&b);
		printf("\n");
	}

	matrix_init(&c, a.n_rows, b.n_cols);

	if (matrix_multiply(&c, &a, &b) < 0) {
		fprintf(stderr, "ERROR: Matrix size mismatch\n");
		exit(1);
	}

	if (print_matrix) {
		printf("c is a %d by %d:\n", c.n_rows, c.n_cols);
		matrix_print(&c);
		printf("\n");
	}

	matrix_destroy(&a);
	matrix_destroy(&b);
	matrix_destroy(&c);

	exit(0);
}
