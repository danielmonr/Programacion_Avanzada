/*
 * =====================================================================================
 *
 *       Filename:  ejercicio4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/04/16 12:21:03
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
#include    <semaphore.h>
#include    <time.h>

#define N_UADS 5
# define T 4

FILE *archivo;
int m[N_UADS];
int alrm[N_UADS];


pthread_t central;
pthread_mutex_t sems[N_UADS*2] = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t file = PTHREAD_MUTEX_INITIALIZER;

void reg(int id);
void crit(int id);
void *funcion(void* arg);
void *central(void *arg);
/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* unidadRegistro(void* arg){

}

void* uadHandler(void* arg){
	uad_t* u = (uad_t*) arg;
}
