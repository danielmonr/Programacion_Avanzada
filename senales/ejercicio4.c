/*
 * =====================================================================================
 *
 *       Filename:  ejercicio4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/02/16 11:03:49
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
#include    <signal.h>

void primer(int);
void segundo(int);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int i;
	void(* funcion)(int);
	signal(SIGINT, primer);

	for (i = 1; i < 11; ++i){
		printf("%d ovejita(s)\n", i);
		sleep(1);
	}

	funcion = signal(SIGINT, segundo);

	for(i = 1; i < 11; ++i){
		printf("%d trineo(s)\n",i);
		sleep(1);
	}

	signal(SIGINT, funcion);

	for(i = 1; i < 11; ++i){
		printf("%d cabrita(s)\n", i);
		sleep(1);
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


void primer(int s){
	printf("Estpy aprendiendo a manejar senales\n");
}

void segundo(int s){
	printf("Ahora cambie de manejador\n");
}
