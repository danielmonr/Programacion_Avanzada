/*
 * =====================================================================================
 *
 *       Filename:  hilos.c
 *
 *    Description:  programa que uiliza threads y un mutex.
 *
 *        Version:  1.0
 *        Created:  14/03/16 10:18:06
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
#include    <unistd.h>

int numero=5;

// Definir un Mutex
pthread_mutex_t mutex;

void* duplicaN(void*);
void* divideN(void*);

struct params {
	int n;
};				/* ----------  end of struct params  ---------- */

typedef struct params param;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	pthread_t hilo1, hilo2;

	param p;
	p.n = 5;

	pthread_create(&hilo1, NULL, duplicaN, &p);
	pthread_create(&hilo2, NULL, divideN, &p);

	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);

	printf("Numero: %d\n", numero);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* duplicaN(void* p){
	int i;
	pthread_mutex_lock(&mutex);
	int temp = numero;
	for(i = 0; i< ((param*)p)->n; i++){
		temp*=2;
		printf("duplica %d\n", temp);
	}
	numero = temp;
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

void* divideN(void* p){
	int i;
	pthread_mutex_lock(&mutex);
	int temp = numero;
	for(i = 0; i < ((param*)p)->n; ++i){
		temp/=2;
		printf("divide %d\n", temp);
	}
	numero = temp;
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}
