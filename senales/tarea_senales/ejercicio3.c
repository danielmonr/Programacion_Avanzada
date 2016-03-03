/*
 * =====================================================================================
 *
 *       Filename:  ejercicio3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/03/16 18:18:05
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
#include    <signal.h>
#include    <sys/types.h>
#include    <unistd.h>
#include    <string.h>

void gestor(int);
char* msg;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int num;
	int* arreglo;
	msg = malloc(30);
	strcpy(msg, "Dato");
	signal(SIGALRM, gestor);
	printf("Ingrese la cantidad de numeros a ingresar: (4<x<19)\n");
	scanf("%d", &num);
	if (num < 5 || num > 9){
		printf("Error el numero asignado no es valido\n");
		abort();
	}

	arreglo = (int*) malloc(num*sizeof(int));

	int i = 0;

	alarm(3);
	for (i; i < num; ++i){
		printf("%s %d:", msg, i);
		scanf("%d", arreglo+i);
	}

	printf("Sus numeros son:\n");
	for (i = 0; i < num; ++i){
		printf("%d: %d\n", i, *(arreglo+i));
	}
	free(arreglo);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void gestor(int sig){
	strcpy(msg,"Dese prisa. Dato");
}
