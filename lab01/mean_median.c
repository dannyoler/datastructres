#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> /* SIZE_MAX */
#include <string.h>
#include <math.h>

void select_sort(int A[], size_t n)
{
	int i, j, temp;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++) {
			if  (A[i] < A[j] ) {
				temp = A[j];
				A[j] = A[i];
				A[i] = temp;
			}
		}
	}

}

int read_array(FILE *fp, int *p_A[])
{
	rewind( fp );
	int tmp, index = 0, n = 0;
	while( !feof(fp) ) {
		fscanf( fp, "%d\n", &tmp );
		n++;
	}
	
	*p_A = malloc( sizeof(int)*n );
	
	rewind( fp );
	while( !feof(fp) ) {
		fscanf( fp, "%d\n", &tmp );
		(*p_A)[index] = tmp;
		index++;
	}
	
	return index;
}

void print_array(const int *A, int n)
{
	int i;
	for ( i=0; i < n; i++ ) {
		//printf( "print Index: %d\tValue: %d\n", i, A[i] );
		printf( "%d ", A[i] );
	}
	printf( "\n" );
}

double mean_array(const int *A, int n)
{
	int i, sum = 0;
	for (i = 0; i < n; i++) {
		sum+= A[i];
	}
	return ( (double) sum / (double) n );

}

double median_array(const int *A, int n)
{
	if ( (double) n / 2.0 == n/2 ) { //n is Even
		return ( ( A[n/2]+A[n/2-1] )/2.0 );
	}
	else { //n is Odd
		return A[n/2];
	}
}
