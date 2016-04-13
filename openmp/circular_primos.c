/*
 * =====================================================================================
 *
 *       Filename:  circular_primos.c
 *
 *    Description:  matrices con numeros, matriz que dice sifcgvuvcfytcxtrucycy el numero correspondiente es circular primo.
 *
 *        Version:  1.0
 *        Created:  11/04/16 11:07:04
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
#include    <math.h>
#include    <time.h>

#define N 1000


char circularPrimo(unsigned short);
char primo(unsigned short);
unsigned short rotar(unsigned short, int);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int i,j;
	unsigned short matriz[N][N];
	char repre[N][N];
	srand((unsigned)time(NULL));
	// llenar matriz con valores aleatorios del 100 al 10 000
	 for(i = 0; i < N; ++i){
		for(j = 0; j <N; ++j){
			matriz[i][j] = (unsigned short)(rand()%9901) + 100;
			repre[i][j] = 0;
		}
	}

/*
	 for(i = 0; i < N; ++i){
		for(j = 0; j <N; ++j){
			printf("matriz[i][j] = %hu\n", matriz[i][j]);
		}
	}*/


	 float start = clock();

#pragma omp parallel shared(matriz, repre) private(i,j)
	 {
#pragma omp for schedule(auto) nowait
		 for(i = 0; i< N; ++i){
			 for(j = 0; j <N ; ++j){
				 repre[i][j] = circularPrimo(matriz[i][j]);
			 }
			 //printf("i= %d\n", i);
		 }
	 }
	 

	 printf("Tiempo en paralelo: %f\n", (clock()-start)/CLOCKS_PER_SEC);

	 for(i = 0; i < N; ++i){
		for(j = 0; j <N; ++j){
			repre[i][j] = 0;
		}
	 }

	 start = clock();
	 for (i = 0; i < N; ++i){
		 for(j = 0; j < N ; ++j){
			 repre[i][j] = circularPrimo(matriz[i][j]);
		 }
	 }

	 printf("Tiempo en serie: %f\n", (clock()-start)/CLOCKS_PER_SEC);


	/*if(primo(197)){
		printf("es primo\n");
		printf("su rotacion es %d\n", rotar(197, 2));
	}
	else{
		printf("no es primo.\n");
	}

	printf("La rotacion de 9080 es %d, su doble rotacion es %d y su triple es %d\n", rotar(9080, 3), rotar(rotar(9080,3),3), rotar(rotar(rotar(9080,3),3),3));*/
/*
	if(circularPrimo(195)){
		printf("Si es circular primo.\n");
	}
	else{
		printf("No lo es\n");
	}
	*/
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

char circularPrimo(unsigned short t){
	unsigned short temp = t;
	char b = 1;
	int n, i;
	if (t == 10000){
		n = 4;
	}
	else if(t >= 1000){
		n = 3;
	}
	else if(t >= 100){
		n = 2;
	}
	else{
		printf("ERROR: %hu\n", t);
	}
	for(i = 0; i < n+1; i++){
		b = b&primo(t);
		t = rotar(t, n);
	}
	return b;
}

char primo(unsigned short t){
	int i;
	if(t <= 1){
		return 0;
	}
	else if(t <= 3){
		return 1;
	}
	else{
		for (i = 4; i < sqrt((double)t); ++i){
			if(t%i == 0)
				return 0;
		}
		return 1;
	}
}

unsigned short rotar(unsigned short t, int n){
	unsigned short r = 0;
	unsigned short temp;
	if (t == 10000){
		//printf("Es 10000\n");
		r = 1;
	}
	else{
		//printf("input: %d\n", t);
		temp = t/(pow(10, n));
		//printf("pow = %f\ntemp = %d\n",pow(10,n), temp);
		r = temp;
		temp *= pow(10, n);
		//printf("Temp a la potencia = %d\n", temp);
		r = r+((t-temp)*10);
		//printf("temp + (t- temp)* potencia menos 1 = %d\n", r);
	}
	return r;
}


