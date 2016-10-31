#include <stdio.h>
#include <malloc.h>

#include "mean_median.h"


int main (int argc, char* argv[])
{
	int *A;

	if (argc < 2) {
		fprintf(stderr, "Usage: mean_median file1 [file2 ...]\n");
	}

	char *file = argv[1];

	FILE *fp = fopen(file, "rb");
	if (fp == NULL)
		return 1;

	int n = read_array(fp, &A);
	if (n < 0) {
		return 1;
	}

	print_array(A, n);
	select_sort(A, n);
	print_array(A, n);

	double mean = mean_array(A, n);
	double med = median_array(A, n);

	printf("mean = %f med = %f\n", mean, med);

	free(A);
	fclose(fp);

	return 0;
}
