/*
 * =====================================================================================
 *
 *       Filename:  filosofos.c
 *
 *    Description:  Ejercicio de filosofos. Una mesa, 4 sillas, 4 platos y tenedores, 3 cuchillos.
 *
 *        Version:  1.0
 *        Created:  16/03/16 19:22:57
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
#include    <unistd.h>
#include    <pthread.h>

#define Lugares 4
#define Tenedores 4
#define Cuchillos 3
#define N 10


struct filosofos {
	int n;
};				/* ----------  end of struct filosofos  ---------- */

typedef struct filosofos Filosofos;

void* comer(void*);

sem_t sillas;
sem_t cuchillos;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	sem_init(&sillas, 0, Lugares);
	sem_init(&cuchillos, 0, Cuchillos);
	pthread_t fil[N];

	int i = 0;
	for (i; i < N; ++i){
		printf("Creando al filosofo n%d...\n", i);
		if(pthread_create(&fil[i], 0, (void*(*)(void*))comer, (void*)i))
			return -1;
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* comer(int info){
	printf("Filosofo %d esperando lugar...\n", info);
	sem_wait(&sillas);
	printf("Filosofo %d esperando cuchillo...\n", info);
	sem_wait(&cuchillos);
	printf("Filosofo %d comiendo...\n", info);
	sleep(rand() % 3+1);
	sem_post(&cuchillos);
	sem_post(&sillas);
	printf("El filosofo %d se levanta de la mesa.\n", info);

	pthread_exit((void *)info);
}
