/*
 * =====================================================================================
 *
 *       Filename:  ejercicio2.c
 *
 *    Description:  Eejrcicio de baño compartido, si hay una mujer dentro solo mujeres pueden entrar, si hay un hombre solo hombres pueden etrar.
 *
 *        Version:  1.0
 *        Created:  29/03/16 18:25:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  ITESM, CSF
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>
#include    <pthread.h>
#include    <unistd.h>
#include    <semaphore.h>
#include    <time.h>

#define num_personas 10

enum Bool {false, true};				/* ----------  end of enum bool  ---------- */
typedef enum Bool bool;

enum persona {HOMBRE, MUJER, RARO};				/* ----------  end of enum persona  ---------- */
typedef enum persona Persona;

static unsigned cont_hombres = 0;
static unsigned cont_mujeres = 0;
static unsigned cont_bano = 0;

static Persona bano = 3;

pthread_mutex_t vacio;

void* usarBano(void*);
void mujerUsaBano();
void hombreUsaBano();

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	pthread_t* personas = (pthread_t*) malloc (num_personas * sizeof(pthread_t));
	srand((unsigned)time(NULL));
	pthread_mutex_init(&vacio, NULL);

	int i;
	for(i = 0;i < num_personas; ++i){
		Persona* p = (Persona*) malloc (sizeof(Persona));
		*p = rand()%2;
		pthread_create(personas+i, NULL, &usarBano, (void*)p);
		sleep(rand()%4);
	}
	for(i = 0; i < num_personas; ++i){
		pthread_join(*(personas+i), NULL);
	}

	free(personas);
	pthread_mutex_destroy(&vacio);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* usarBano(void* arg){
	Persona* p = (Persona*) arg;

	switch(*p){
		case MUJER:
			cont_mujeres++;
			printf("=>Llega una Mujer.(%d en espera)\n", cont_mujeres);
			mujerUsaBano();
			break;
		case HOMBRE:
			cont_hombres++;
			printf("=>Llega un hombre.(%d en espera)\n", cont_hombres);
			hombreUsaBano();
			break;
		defualt:
			printf("Llego un raro\n");
			pthread_exit(NULL);
			return;
			break;
	}

	free(p);
	pthread_exit(NULL);
	return;
}

void mujerUsaBano(){
	if(bano != MUJER){
		pthread_mutex_lock(&vacio);
		bano = MUJER;
	}
	cont_bano++;
	cont_mujeres--;
	printf("Entra una mujer.(%d en espera)\n", cont_mujeres);
	sleep(rand()%10);
	printf("Sale una mujer\n");
	cont_bano--;
	if(cont_bano == 0){
		pthread_mutex_unlock(&vacio);
		bano = 3;
	}
}

void hombreUsaBano(){
	if(bano != HOMBRE){
		pthread_mutex_lock(&vacio);
		bano = HOMBRE;
	}
	cont_bano++;
	cont_hombres--;
	printf("Entra un hombre.(%d en espera)\n", cont_hombres);
	sleep(rand()%4);
	printf("Sale un hombre\n");
	cont_bano--;
	if(cont_bano == 0){
		pthread_mutex_unlock(&vacio);
		bano = 3;
	}
}
