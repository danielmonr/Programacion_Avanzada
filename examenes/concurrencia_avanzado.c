/*
 * =====================================================================================
 *
 *       Filename:  concurrencia_avanzado.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  31/03/16 10:52:04
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
#include    <semaphore.h>
#include    <pthread.h>
#include    <time.h>

#define C 10
#define S 3
#define U 50
#define T 3
#define N 100

struct sala {
	int id;
	sem_t asientos;
};				/* ----------  end of struct Sala  ---------- */

typedef struct sala Sala;

struct complejos {
	int id;
	Sala *salas;
	sem_t taquillas;
};				/* ----------  end of struct complejos  ---------- */

typedef struct complejos Complejos;

void* handler(void*);
Complejos* cines;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){

	int i;
	cines = (Complejos*) malloc(C * sizeof(Complejos));
	srand((unsigned)time(NULL));

	for(i = 0; i < C; ++i){
		(cines+i)->id = i;
		(cines+i)->salas = (Sala*) malloc (S * sizeof(Sala));

		sem_init((&(cines+i)->taquillas), 0, T);

		int j;
		for(j = 0; j < S; ++j){
			(((cines+i)->salas)+j)->id = j;
			sem_init(&((((cines+i)->salas)+j)->asientos), 0, U);
		}
	}

	int* ids = (int*) malloc (N* sizeof(int));
	for(i = 0; i < N; ++i){
		*(ids+i) = i;
	}

	pthread_t* clientes = (pthread_t*) malloc(N*sizeof(pthread_t));
	pthread_t *aux;
	printf("Empiezan a llegar clientes.\n");

	i = 0;
	for(aux= clientes; aux<(clientes+N); ++aux){
		pthread_create(aux, 0, handler, (void*)(ids+i));
		++i;
	}


	for(aux = clientes; aux < (clientes+N); ++aux){
		pthread_join(*aux, NULL);
	}
	
	for(i = 0; i < C; ++i){
		sem_destroy(&((cines+i)->taquillas));
		int j;
		for(j = 0; j< S; ++j){
			sem_destroy(&((((cines+i)->salas)+j)->asientos));
		}
		free((cines+i)->salas);
	}
	free(ids);
	free(clientes);
	free(cines);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* handler(void* arg){
	int status = -1;
	int* cli = (int*)arg;
	Complejos* c = (cines + rand()%C);
	Sala* s = ((c->salas)+rand()%S);
	printf("Llega el cliente %d al cine %d, pide boleto para la sala %d\n", *cli, c->id, s->id);
	sem_wait(&(c->taquillas));
	printf("Cliente %d pide en la taquilla\n", *cli);
	status = sem_trywait(&(s->asientos));
	if(status == 0)
		printf("Cliente %d reservo en el cine %d, en la sala %d\n", *cli, c->id, s->id);
	else
		printf("Cliente %d no pudo reservar, sala llena.\n", *cli);

	sem_post(&(c->taquillas));

	pthread_exit(NULL);
}
