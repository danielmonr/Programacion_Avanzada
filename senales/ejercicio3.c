/*
 * =====================================================================================
 *
 *       Filename:  ejercicio3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/02/16 10:56:02
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

void manejar(int);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){

	signal(SIGINT, manejar);
	signal(SIGTSTP, manejar);

	int i = 10;

	for (i; i> 0; --i){
		printf("%d\n", i);
		sleep(1);
	}


	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void manejar(int c){
	if (c == SIGTSTP)
		printf("Se mando un Ctr+Z\n");
	else if (c == SIGINT)
		printf("Se mando un Ctr+C\n");
}
