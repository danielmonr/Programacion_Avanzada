/*
 * =====================================================================================
 *
 *       Filename:  secciones.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/04/16 10:50:45
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
	int n = 100, i;
	float a[n], b[n], c[n], d[n];
	for(i = 0; i < n; i++){
		a[i] = b[i] = i*22.0;
	}
#pragma omp parallel shared(a,b,c,d) private(i)
	{
#pragma omp sections nowait
		{
#pragma omp section
			{
				for (int i = 0; i < n; i++){
					c[i]=a[i]+b[i];
				}
			}
#pragma omp section
			{
				for (int i = 0; i < n; i++){
					d[i] = a[i]*b[i];
				}
			}
		}
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
