/*
 * =====================================================================================
 *
 *       Filename:  ejercicio3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  29/03/16 19:56:28
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
#include    <time.h>
#include    <unistd.h>
#include    <pthread.h>
#include    <semaphore.h>

#define N 5
#define Peso_max 50
#define peso_robot 10
#define NUM_ROBOTS 10

struct seccion {
	int id;
	sem_t peso;
};				/* ----------  end of struct seccion  ---------- */


struct robot {
	int id;
};				/* ----------  end of struct robot  ---------- */

typedef struct robot robot_t;

typedef struct seccion seccion_t;
seccion_t* secciones;

void* robotHandler(void * arg);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	srand((unsigned)time(NULL));
	int i;
	robot_t* robots = (robot_t*) malloc (NUM_ROBOTS * sizeof(robot_t));
	for(i = 0; i < NUM_ROBOTS; ++i){
		(robots+i)->id = i;
	}
	secciones = (seccion_t*) malloc (N* sizeof(seccion_t));
	for(i = 0; i < N; ++i){
		(secciones+i)->id = i;
		sem_init(&(secciones+i)->peso, 0, Peso_max / peso_robot);
	}

	pthread_t* robot_pt = (pthread_t*) malloc (NUM_ROBOTS * sizeof(pthread_t));

	for(i = 0; i < NUM_ROBOTS; ++i){
		pthread_create(robot_pt+i, NULL, &robotHandler, (void*)(robots+i));
	}

	for(i = 0; i< NUM_ROBOTS; ++i){
		pthread_join(*(robot_pt+i), NULL);
	}


	for(i = 0; i < N; ++i){
		sem_destroy(&(secciones+i)->peso);
	}

	free(secciones);
	free(robots);
	free(robot_pt);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* robotHandler(void* arg){
	robot_t* r = (robot_t*) arg;
	int i;
	for (i = 0; i < N; ++i){
		sem_wait(&(secciones+i)->peso);
		printf("El robot %d, entra a la seccion %d.\n", r->id, (secciones+i)->id);
		sleep(rand()%7);
		printf("El robot %d, sale de la seccion %d.\n", r->id, (secciones+i)->id);
		sem_post(&(secciones+i)->peso);
	}

	printf("El robot %d acabo su recorrido.\n", r->id);
	pthread_exit(NULL);
}
