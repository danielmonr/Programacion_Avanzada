/*
 * =====================================================================================
 *
 *       Filename:  barreras.c
 *
 *    Description:  Programacion de barreras
 *
 *        Version:  1.0
 *        Created:  28/03/16 10:25:54
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
#include    <unistd.h>

#define num_threads 5

static pthread_barrier_t barrera;

void* funcion(void*);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	srand((unsigned)time(NULL));
	// Inicializacion de barrera, (barrera, atributos, numero de hilos a esperar)
	pthread_barrier_init(&barrera, NULL, 5);
	pthread_t *threads = (pthread_t*) malloc (num_threads * sizeof(pthread_t));
	int* ids = (int*)malloc(5*sizeof(int));
	int i;
	for (i = 0; i < num_threads; ++i){
		*(ids+i) = i;
		pthread_create(threads+i, NULL, funcion, (void*)(ids+i));
	}
	for (i = 0; i < num_threads; ++i){
		pthread_join(threads[i], NULL);
	}

	free(ids);
	free(threads);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* funcion(void* n){
	int* id = (int*)n;
	int i;
	for (i = 0; i < 10; ++i){
		printf("Hilo %i ejecutando accion.\n", *id);
		sleep(rand()%5);
	}
	pthread_barrier_wait(&barrera);
	printf("Hilo %i termino.\n", *id);
	pthread_exit(NULL);
}
