/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  18/04/16 10:13:13
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
#include    <time.h>

#define N 5000
struct punto {
	float x;
	float y;
	struct punto* c;
};				/* ----------  end of struct punto_t  ---------- */

typedef struct punto punto_t;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	srand((unsigned)time(NULL));
	punto_t * arreglo = (punto_t *) malloc (N * sizeof(punto_t));
	printf("el tamano es %d\n", sizeof(punto_t));
	int i;
	float** distancias = (float**) malloc (N*sizeof(float*));
	punto_t* c1 = (punto_t*) malloc (sizeof(punto_t));
	punto_t* c2 = (punto_t*) malloc (sizeof(punto_t));
	c1->x = 0.23;
	c1->y = 0.32;
	c2->x = 0.01;
	c2->y = 0.02;

	for (i = 0;i < N;i++){
		*(distancias+i) = (float*) malloc (2 * sizeof(float));
	}

#pragma omp parallel shared(arreglo, distancias) private(i)
	{
#pragma omp for schedule(auto) nowait
			for(i = 0; i < N; ++i){
				(*(arreglo+i)).x = (rand()%100)/100;
				(*(arreglo+i)).y = (rand()%100)/100;
			}

	}

#pragma omp parallel shared(arreglo, distancias, c1, c2) private(i)
	{
#pragma omp for nowait
		for(i = 0; i < N; ++i){
			distancias[i][0] = (c1->x - arreglo[i].x)/(c1->y - arreglo[i].y);
			distancias[i][1] = (c2->x - arreglo[i].x)/(c2->y - arreglo[i].y);
		}
#pragma omp 
	}

	printf("Acabo\n");
	free(distancias);
	free(c1);
	free(c2);
	free(arreglo);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
