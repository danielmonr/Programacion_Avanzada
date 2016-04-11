/*
 * =====================================================================================
 *
 *       Filename:  ejemplo.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/04/16 10:37:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>
#include    <omp.h>

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int i, n=100, chunk=30, tid;
	float a[n], b[n], c[n];

	for(i = 0; i < n; i++){
		a[i]= b[i] = i*22.0;
	}
#pragma omp parallel shared(a,b,c,chunk) private (i, tid)
	{
#pragma omp for schedule(auto) ordered nowait
		for(i = 0; i<n; i++){
			tid = omp_get_thread_num();
			c[i] = a[i] + b[i];
			printf("tid\n %d i %d\n", tid, i);
		}
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
