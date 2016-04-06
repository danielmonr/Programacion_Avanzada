/*
 * =====================================================================================
 *
 *       Filename:  concurrencia2.c
 *
 *    Description:  Considere un sistema con tres procesos fumadores y un proceso agente. Cada fumador tarda en promedio 10 segundo fumando y luego espera 20 segundos antes de fumar su siguiente cigarrillo. Además, para fumar se requiere unir los siguientes ingredientes: tabaco, papel y fósforos. Los ingredientes se obtienen de cada fumador ya que cada uno es un productor ilimitado de algún ingrediente. El agente es el encargado de colocar los ingredientes sobre una “mesa” y ponerlos disponibles para los fumadores. El agente pide a cada fumador su ingrediente correspondiente, pero si el fumador está fumando, entonces el agente se salta dicho ingrediente y va a conseguir los restantes. Si no hay ningún ingrediente disponible, el agente se va a hacer otras actividades. El proceso de solicitar un ingrediente y colocarlo sobre la mesa se realiza cada 15 segundos (cuando termina sus múltiples ocupaciones). El agente está en un proceso infinito de conseguir los ingredientes y ponerlos disponibles para los fumadores.
 *
 *        Version:  1.0
 *        Created:  07/04/16 10:02:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <unistd.h>
#include    <semaphore.h>
#include    <pthread.h>
#include    <stdio.h>

#define F 3
#define TF 10
#define ESPERA 20


struct fumador {
	int id;
	pthread_mutex_t fumando;
};				/* ----------  end of struct fumador  ---------- */

typedef struct fumador fumador_t;

pthread_mutex_t tabaco;
pthread_mutex_t papel;
pthread_mutex_t fosforos;

fumador_t * f;

void* fumar(void*);
void* agente(void*);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	f = (fumador_t*) malloc (F * sizeof(fumador_t));
	int i;
	for (i = 0; i < F; ++i){
		(f+i)->id = i;
		pthread_mutex_init(&(f+i)->fumando, NULL);
	}
	pthread_mutex_init(&tabaco, NULL);
	pthread_mutex_init(&papel, NULL);
	pthread_mutex_init(&fosforos, NULL);
	pthread_mutex_trylock(&tabaco);
	pthread_mutex_trylock(&papel);
	pthread_mutex_trylock(&fosforos);


	pthread_t * fumadores = (pthread_t*) malloc (F * sizeof (pthread_t));
	pthread_t ag;

	pthread_create(&ag, NULL, &agente, NULL);

	for (i = 0; i < F; ++i){
		pthread_create(fumadores+i, NULL, &fumar, (void*)(f+i));
	}


	pthread_join(*fumadores, NULL);

	free(fumadores);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


void* fumar(void * arg){
	fumador_t * fu = (fumador_t*) arg;
	//printf("%d\n", fu->id);
	while(1){
		pthread_mutex_lock(&tabaco);
		pthread_mutex_lock(&papel);
		pthread_mutex_lock(&fosforos);
		pthread_mutex_lock(&(fu->fumando));
		printf("Fuamdor %d esta fumando.\n", fu->id);
		sleep(10);
		printf("Fumador %d acabo de fumar.\n", fu->id);
		pthread_mutex_unlock(&(fu->fumando));
		sleep(20);
	}

}

void *agente(void* arg){
	while(1){
		int status;
		status = pthread_mutex_trylock(&(f->fumando));
		if (status == 0){
			pthread_mutex_unlock(&(f->fumando));
			pthread_mutex_unlock(&tabaco);
		}
		status = pthread_mutex_trylock(&((f+1)->fumando));
		if (status == 0){
			pthread_mutex_unlock(&((f+1)->fumando));
			pthread_mutex_unlock(&papel);
		}
		status = pthread_mutex_trylock(&((f+2)->fumando));
		if (status == 0){
			pthread_mutex_unlock(&((f+2)->fumando));
			pthread_mutex_unlock(&fosforos);
		}
		sleep(15);
	}
}
