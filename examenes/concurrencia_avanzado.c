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
#include    <semaphore.h>

#define C 10
#define S 3
#define U 50
#define T 3

struct sala {
	sem_ti asientos;
};				/* ----------  end of struct Sala  ---------- */

typedef struct sala Sala;

struct complejos {
	Sala *salas;
	sem_t *taquillas;
};				/* ----------  end of struct complejos  ---------- */

typedef struct complejos Complejos;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){

	int i;
	Complejos* cines = (Complejos*) malloc(C * sizeof(Complejos));

	for(i = 0; i < C; ++i){
		(cines+i)->salas = (Sala*) malloc (S * sizeof(Sala));
		(cines+i)->taquillas = (sem_t*) malloc (T * sizeof(sem_t));

		int j;
		for(j = 0;j < T; ++j){
			sem_init(((cines+i>->taquillas)+j), 0, T);
		}
		for(j = 0; j < S; ++j){
			sem_init((((cines+i)->salas)+j), 0, U);
		}
	}

	
	for(i = 0; i < C; ++i){
		free((cines+i)->salas);
		free((cines+i)->taquillas);
	}

	free(cines);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
