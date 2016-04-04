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


struct uad {
};				/* ----------  end of struct uad  ---------- */

typedef struct uad uad_t;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* unidadRegistro(void* arg){

}

void* uadHandler(void* arg){
	uad_t* u = (uad_t*) arg;
}
