/*
 * =====================================================================================
 *
 *       Filename:  ejercicio1.c
 *
 *    Description:  Escriba un programa en C que reciba por teclado numeros y cada vez que recibe uno,
 *    				genera un hijo que calcula e imprime el factorial de ese numero. (NO SIRVE)
 *
 *        Version:  1.0
 *        Created:  28/01/16 11:00:56
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
#include	<unistd.h>

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	pid_t pid;
	int num = 1;
	while(num != 0){
		printf(">>");
		scanf("%d", &num);
		pid = fork();

		if(pid == -1)
			printf("Error al crear al hijo\n");
		else if (pid == 0){
			int i;
			for( i = 1; i < num; i++){
				num *=i;
			}
			printf("Factorial: %d\n", num);
			break;
		}
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
