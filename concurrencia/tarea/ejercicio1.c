/*
 * =====================================================================================
 *
 *       Filename:  ejercicio1.c
 *
 *    Description:  Blancanieves y los siete enanitos viven en una casa donde solo existen cuatro sillas, que los enanitos utilizan para comer. Cuando un enanito vuelve de trabajar en la mina comprueba si hay una silla libre para sentarse. Si existe una silla libre, entonces indica a Blancanieves que ya está sentado, y espera pacientemente su turno a que le sirvan. Cuando le ha servido, Blancanieves le indica que puede empezar a comer. El enanito come y cuando acaba, deja la silla libre y vuelve a la mina. Por su parte, Blancanieves cuando no tiene ningún enanito pendiente de servirle, se va a dar una vuelta.
 *
 *     
 *
 *     a)Realice un análisis exhaustivo de los problemas de concurrencia que se pueden dar en un sistema de este tipo, planteando cada uno de ellos y explicándolo.
 *
 *     b)Seleccione una técnica de concurrencia para solucionar el problema, explicando los motivos de su selección.
 *
 *     c)Partiendo del análisis realizado y la técnica de concurrencia seleccionada, programe una solución que resuelva el problema descrito. Utilizar únicamente dos tipos de procesos: Enanito y Blancanieves.
 *
 *        Version:  1.0
 *        Created:  29/03/16 18:23:24
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



struct enanito {
	int id;
	pthread_mutex_t servido;
};				/* ----------  end of struct enanito  ---------- */

typedef struct enanito Enanito;


int cont;
sem_t sillas;
sem_t ocupadas;

Enanito* mesa[4];

void* enanitoHandler(void * arg){
	Enanito* e = (Enanito*) arg;
	printf("Enanito %d se va a las minas.\n", e->id);
	sleep(rand()%15);
	printf("Enanito %d, llega de las minas\n", e->id);
	int i;
	sem_wait(&sillas);
	printf("Enanito %d se sienta en la mesa.\n", e->id);
	for (i = 0; i < 4; ++i){
		if(mesa[i] == NULL){
			mesa[i] = e;
			sem_post(&ocupadas);
			pthread_mutex_trylock(&(e->servido));
			break;
		}
	}
	pthread_mutex_lock(&(e->servido));
	sleep(2);
	printf("Enanito %d acabo de comer y se va las minas.\n", e->id);
	mesa[i] = NULL;
	sem_post(&sillas);
	pthread_exit(NULL);
}

void* snowHandler(void* arg){
	int cont = 0;
	int status;
	while(cont < 7){
		int t, i;
		sem_getvalue(&ocupadas, &t);
		printf("T = %d\n", t);
		if (t > 0){
			for(i = 0; i < 4; ++i){
				if (mesa[i] != NULL){
					pthread_mutex_unlock(&(mesa[i]->servido));
					printf("Snow le da de comer a Enanito %d.\n", mesa[i]->id);
					sem_trywait(&ocupadas);
					cont++;
				}
			}
		}
		else{
			printf("Snow se va a dar una vuelta.\n");
			sleep(5);
		}
	}
	printf("todos los enanitos comieron.\n");
	pthread_exit(NULL);
}

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	srand((unsigned)time(NULL));
	sem_init(&sillas, 0, 4);
	sem_init(&ocupadas, 0, 0);
	Enanito* enanitos = (Enanito*) malloc (7 * sizeof(Enanito));
	int i;
	for (i = 0; i < 7; ++i){
		(enanitos+i)->id = i+1;
		pthread_mutex_init(&(enanitos+i)->servido, NULL);
	}

	pthread_t * ens_pt = (pthread_t*) malloc (7 * sizeof(pthread_t));
	pthread_t snow_pt;
	pthread_create(&snow_pt, NULL, &snowHandler, NULL);

	for(i = 0; i < 7; ++i){
		pthread_create(ens_pt+i, NULL, &enanitoHandler, (void*)(enanitos+i));
	}

	pthread_join(snow_pt, NULL);
	printf("SE destruye todo\n");
	sem_destroy(&sillas);
	sem_destroy(&ocupadas);
	free(ens_pt);
	free(enanitos);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
