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
	int num;
};				/* ----------  end of struct args  ---------- */

typedef struct args args_t;


struct par {
	int uno;
	int dos;
};				/* ----------  end of struct par  ---------- */

typedef struct par par_t;

char** tablero;
par_t** soluciones;
pthread_t* threads;
int n;

void* resolver(void*);
void* llenar(int);
void manejador(int s);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	srand(time(NULL));
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
	soluciones = (par_t**) malloc (NUM_PROC*sizeof(par_t*));
	for (i = 0; i < NUM_PROC; ++i){
		*(soluciones+i) = (par_t*) malloc (n*n/NUM_PROC);
	}


	for (i = 0; i < sqrt(NUM_PROC); ++i){
		ag[i].tam = sqrt(n*n/NUM_PROC);
		ag[i].ini = ag[i].tam * i;
		pthread_create((threads+i), 0, &resolver, &ag[i]);
	}

	for ( i = 0; i < NUM_PROC; ++i){
		pthread_join(*(threads+i), NULL);
	}
	

	printf("Solucion:\n");
	for (i = 0; i < NUM_PROC; ++i){
		for(j = 0; j < n*n/NUM_PROC; ++j){
			if(((*(soluciones+i))+j)->uno && ((*(soluciones+i))+j)->dos)
				printf("(%d,%d)", ((*(soluciones+i))+j)->uno, ((*(soluciones+i))+j)->dos);
		}
	}
	printf("\n");


	for ( i = 0; i < n; ++i)
		free(*(tablero+i));
	free(tablero);
	free(threads);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* resolver(void* arg){
	args_t* ag = (args_t*)arg;
	printf("%d\n", ag->ini);
	int i, j;
	int cont = 1;
	*((*(tablero + ag->ini))+ag->ini) = 0;
	*(*(tablero+ag->ini+ag->tam-1)+ag->ini+ag->tam-1) = 0;
	(*(soluciones+ag->num))->uno = ag->ini;
	(*(soluciones+ag->num))->dos = ag->ini;
	for(i = ag->ini+1; i < ag->tam; ++i){
		if (!(*((*(tablero+i))+i))){
			((*(soluciones+ag->num))+cont)->uno = i;
			((*(soluciones+ag->num))+cont)->dos = i;
		}
		else{
			for (j = i+1; j < ag->tam; ++j){
				if(!(*((*(tablero+i))+j)) && !(*((*(tablero+i+1))+j))){
					((*(soluciones+ag->num))+cont)->uno = j;
					((*(soluciones+ag->num))+cont)->dos = i;
					((*(soluciones+ag->num))+cont)->uno = j;
					((*(soluciones+ag->num))+cont)->dos = i+1;
				}
			}
		}
	}
}

void manejador(int s){
	int i, j;
	for (i = 0; i < NUM_PROC; ++i){
		printf("Procesador %d:\n", i);
		for (j = 0; j < (n*n/NUM_PROC); ++j){
			printf("(%d,%d),", (*(soluciones+i)+j)->uno, (*(soluciones+i)+j)->dos);
		}
		printf("\n");
	}
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
