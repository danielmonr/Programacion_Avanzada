/*
 * =====================================================================================
 *
 *       Filename:  openmp_avanzado.c
 *
 *    Description:  Dos secciones en la 1a entras a una region critica y realizas 4 operaciones, en la segunda seccion realizas varias op.
 *
 *        Version:  1.0
 *        Created:  14/04/16 10:28:31
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

	int * arreglo = (int*) malloc (6* sizeof(int));
	int i, cont = 0, cont2= 0;

#pragma omp parallel shared(arreglo, cont, cont2) private(i)
	{
#pragma omp sections nowait
		{
#pragma omp section
			{
#pragma omp critical
				{
#pragma omp num_thread(4) parallel
					{
						printf("operacion %d", omp_get_thread_num());
#pragma omp atomic
							cont++;
					}
				}

			}
#pragma omp section
			{
#pragma omp prallel for schedule (auto)
				{
					for(i = 0; i < 6; ++i){
						arreglo[i] = i;
					}
				}
				for (i = 0; i < 6; ++i){
					cont2 += arreglo[i];
				}
			}
		}
	}

	printf("Cont 2i: %d\n", cont2);

	free(arreglo);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
