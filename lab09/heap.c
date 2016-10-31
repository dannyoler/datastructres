#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

struct heap {
	int *A;
	size_t n_max;
	size_t n;
};

int heap_init(struct heap *h, size_t n_max)
{
	/* Allocate memory for the array, initialize all of the
	 * members of h.
	 * Return 0 on success, -1 on failure.
	 */
	h->A = malloc( sizeof( int ) * n_max );
	
	if ( h->A == NULL ) { return -1; }
	
	h->n_max = n_max;
	h->n = 0;

	return 0;
}

/* heap_insert inserts a new element into the heap in the correct location.
 * Return 0 on success, -1 on failure.
 */

/* Index conversions:
 * Parent: (pos - 1) /2
 * Left  : 2*pos + 1
 * Right : 2*pos + 2
 */

int heap_insert(struct heap *h, int data)
{
	if (h->n == h->n_max) {
		/* Reallocate space as needed using 2x the previous
		 * amount allocated.
		 */
		h->A = realloc( h->A, sizeof( int )*(h->n_max)*2 );
		
		if ( h->A == NULL ) {
			return -1;
		}
		else {
			h->n_max*=2;
		}
	}

	/* Temporarily put the new element in the last position, and
	 * walk back to the root, swapping as needed.
	 */

	int pos = h->n;
	h->A[pos] = data;
	h->n++;
	
	int parent_pos = (pos - 1)/2;
	while ( parent_pos >= 0 && ( h->A[pos] < h->A[parent_pos] ) ) {
		h->A[pos] = h->A[parent_pos];
		h->A[parent_pos] = data;
		
		pos = parent_pos;
		parent_pos = (parent_pos - 1)/2;
	}

	return 0;
}

/* heap_delete removes the top element (i.e. smallest) element from
 * the heap and copies it into *p_min.
 * Return 0 on success, -1 on failure (heap is empty).
 */

int heap_delete(struct heap *h, int *p_min)
{
	if (h == NULL || h->n == 0) {
		return -1;
	}
	
	/* Copy out the minimum element, swap the last element into
	 * the top position, and decrease the array count.
	 */
	
	*p_min = h->A[0];
	h->n--;
	h->A[0] = h->A[h->n];

	/* Now walk down the tree starting from the root, making sure
	 * the element at the current position is smaller than both
	 * children.
	 */
	int pos = 0, L, R, tmp;
	while (pos < h->n) {
		/* Remember that a node may have two, one, or zero
		 * children and all three cases must be handled.
		 */
		L = 2*pos + 1;
		R = 2*pos + 2;
		
		if ( R < h->n ) { //Two children
			if ( h->A[L] <= h->A[R] && h->A[L] < h->A[pos] ) { //Left smaller than right and parent
				tmp = h->A[L];
				h->A[L] = h->A[pos];
				h->A[pos] = tmp;
			}
			else if ( h->A[R] < h->A[L] && h->A[R] < h->A[pos] ) { //Right smaller than left and parent
				tmp = h->A[R];
				h->A[R] = h->A[pos];
				h->A[pos] = tmp;
			}
			else { break; }
		}
		else if ( L < h->n && R >= h->n ) { //Only Left Child
			if ( h->A[L] < h->A[pos] ) { //Left smaller than parent
				tmp = h->A[L];
				h->A[L] = h->A[pos];
				h->A[pos] = tmp;
			}
			else { break; }
		}
		else { //No Children
			break;
		}
		
		pos++;
	}

	return 0;
}

/* destroy all dynamic memory associated with the heap */
void heap_destroy(struct heap *h)
{
	/* fill in your code here */
	free( h->A );
}


/* helper function returns 1 if the heap is valid and 0 otherwise.
 */
int heap_validate(const struct heap *h)
{
	int rc = 1;
	int i;
	for (i=0; i < h->n; i++) {
		int L = 2*i + 1;
		int R = 2*i + 2;
		if (L < h->n && h->A[i] > h->A[L]) {
			fprintf(stderr, "heap_validate failed at position %d, elements %d and %d\n", i, h->A[i], h->A[L]);
			rc = 0;
			break;
		}
		if (R < h->n && h->A[i] > h->A[R]) {
			fprintf(stderr, "heap_validate failed at position %d, elements %d and %d\n", i, h->A[i], h->A[R]);
			rc = 0;
			break;
		}
	}

	return rc;
}

/* helper function to print the elements of the heap
 */
void heap_print(const struct heap *h)
{
	int i;
	for (i=0; i<h->n; i++) {
		printf("%2d ", h->A[i]);
	}
	printf("\n\n");
}


int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: heap data_file.txt\n");
		return 1;
	}

	FILE *fp_data = fopen(argv[1], "rb");
	if (fp_data == NULL) {
		fprintf(stderr, "Error opening %s\n", argv[1]);
		return 1;
	}

	int data;
	struct heap h;
	heap_init(&h, 1);

	while (!feof(fp_data) && !ferror(fp_data)) {
		if (fscanf(fp_data, "%d", &data) != 1)
			continue;
		
		if (heap_insert(&h, data) < 0) {
			fprintf(stderr, "Error while inserting into heap: %s\n", strerror(errno));
		}

		//heap_print(&h);

		// if (heap_validate(&h) == 0) {
		// 	abort();
		// }
	}

	printf("Delete items:\n");

	while (h.n > 0) {
		int item;
		if (heap_delete(&h, &item) < 0) {
			fprintf(stderr, "Error while deleting from heap: %s\n", strerror(errno));
			break;
		}
		printf("%d\n", item);

		// if ( heap_validate(&h) == 0) {
		// 	abort();
		// }
	}
	printf("\n Ran successfully\n");

	heap_destroy(&h);

	fclose(fp_data);

	return 0;
}
