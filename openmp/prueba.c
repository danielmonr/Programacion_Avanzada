/*
 * =====================================================================================
 *
 *       Filename:  prueba.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/04/16 10:23:23
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
#include <omp.h>

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int nthreads, tid;
#pragma omp parallel private(tid)
	{
	tid = omp_get_thread_num();
	printf("\nprueba");
	if(tid == 0){
		nthreads=omp_get_num_threads();
		printf("\nNT: %d", nthreads);
	}
}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
