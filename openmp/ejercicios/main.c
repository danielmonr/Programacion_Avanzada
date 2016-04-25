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
	unsigned short ref;
};				/* ----------  end of struct punto_t  ---------- */

typedef struct punto punto_t;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	srand((unsigned)time(NULL));
	punto_t * arreglo = (punto_t *) malloc (N * sizeof(punto_t));
	//printf("el tamano es %d\n", sizeof(punto_t));
	int i, contx1, conty1, contx2, conty2, cont1, cont2;
	contx1 = contx2 = conty1 = conty2 = 0;
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

	while((c1->x + c1->y) > 0.01 && (c2->x + c2->y) > 0.01){
		printf("ok\n");

#pragma omp parallel shared(arreglo, distancias, c1, c2, cont1, cont2) private(i)
		{
#pragma omp for nowait reduction(+: cont1, cont2)
			for(i = 0; i < N; ++i){
				distancias[i][0] = (c1->x - arreglo[i].x)/(c1->y - arreglo[i].y);
				distancias[i][1] = (c2->x - arreglo[i].x)/(c2->y - arreglo[i].y);
				if ( distancias[i][0] < distancias[i][1]){
					arreglo[i].ref = 1;
					cont1++;
				}
				else{
					arreglo[i].ref = 2;
					cont2++;
				}
			}
#pragma omp barrier
#pragma omp for reduction (+: contx1, conty1, contx2, conty2)
			for(i = 0; i < N; ++i){
				if(arreglo[i].ref == 1){
					contx1 += arreglo[i].x;
					conty1 += arreglo[i].y;
				}
				else{
					contx2 += arreglo[i].x;
					conty2 += arreglo[i].y;
				}
			}
#pragma omp barrier
#pragma omp master
			{
				c1->x = contx1 / cont1;
				c1->y = conty1 / cont1;
				c2->x = contx2 / cont2;
				c2->y = conty2 / cont2;
				printf("C1 x= %f y = %f, C2 x= %f y = %f\n", c1->x, c1->y, c2->x, c2->y);
				//contx1 = contx2 = conty1 = conty2 = cont1 = cont2 = 0;
			}

		}
	}

	printf("C1 x= %f y = %f, C2 x= %f y = %f\n", c1->x, c1->y, c2->x, c2->y);

	printf("Acabo\n");
	free(distancias);
	free(c1);
	free(c2);
	free(arreglo);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
