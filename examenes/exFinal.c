/*
 * =====================================================================================
 *
 *       Filename:  exFinal.c
 *
 *    Description:  Examen final
 *
 *        Version:  1.0
 *        Created:  12/05/16 08:05:06
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
#include    <pthread.h>
#include    <time.h>
#include    <math.h>
#include    <unistd.h>
#include    <signal.h>

#define NUM_PROC 4


struct args {
	int ini;
	int tam;
};				/* ----------  end of struct args  ---------- */

typedef struct args args_t;

char** tablero;
int** soluciones;
pthread_t* threads;

void* resolver(void*);
void* llenar(int);
void manejador(int s);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	srand(time(NULL));
	int n;
	printf("N >> ");
	scanf("%d", &n);
	int i, j;
	tablero = (char**) malloc (n* sizeof(char*));
	for (i=0; i < n; ++i){
		*(tablero+i) = (char*) malloc (n* sizeof(char));
	}
	llenar(n);

	args_t ag[NUM_PROC];
	threads = (pthread_t*) malloc (NUM_PROC*sizeof(pthread_t));
	signal(SIGUSR1, manejador);

	for (i = 0; i < NUM_PROC; ++i){
		ag[i].tam = sqrt(n*n/NUM_PROC);
		ag[i].ini = ag[i].tam * i;
		pthread_create((threads+i), 0, &resolver, (void*)&ag[i]);
	}

	for ( i = 0; i < NUM_PROC; ++i){
		pthread_join(*(threads+i), NULL);
	}


	for ( i = 0; i < n; ++i)
		free(*(tablero+i));
	free(tablero);
	free(threads);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* resolver(void* arg){
	args_t* ag = (args_t*)arg;
	int i, j;
	for (i = ag->ini; i < ag->ini + ag->tam; ++i){
		for(j = ag->ini; j < ag->ini + ag->tam; ++j){
			
		}
	}
}

void manejador(int s){

}

void* llenar(int n){
	int i, j;
	for (i = 0; i < n; ++i){
		for(j = 0; j < n; ++j){
			*((*(tablero+i))+j) = (rand()%100 < 20 ? 1 : 0);
		}
	}
}

void imprimir(int n){
	int i, j, temp;
	for(i = 0; i < n; ++i){
		for (j = 0; j < n; ++j){
			temp = *((*(tablero+i))+j);
			printf("%d ", temp);
		}
		printf("\n");
	}
}
