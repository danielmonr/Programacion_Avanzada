/*
 * =====================================================================================
 *
 *       Filename:  ejercicio2.c
 *
 *    Description:  Escriba un programa en C que genere dos procesos. El primer proceso lee números
 *    enteros del teclado y los envía a un pipe para que los lea el otro proceso. El segundo
 *    proceso recibirá los números del pipe sumándolos. Cuando se entre el número 0, el
 *    proceso hijo debe mostrar el resultado de la suma y ambos procesos deben terminar.
 *
 *        Version:  1.0
 *        Created:  11/02/16 10:10:35
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
#include    <wait.h>

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	pid_t pid;

	int pipa[2];
	pipe(pipa);

	pid = fork();
	if(pid < 0 ){
		printf("Error al crear el hijo\n");
		return 0;
	}
	else if (pid == 0){
		close(pipa[1]);
		int c, r;
		c = -1;
		r = 0;
		int t;
		while(c != 0){
			sleep(1);
			t = read(pipa[0], &c, sizeof(int));
			r += c;
	//		printf("Leido %d\n", c);
		}

		printf("Suma: %d", r);

	}
	else{
		close(pipa[0]);
		int c = -1;
		while(c != 0){
			printf(">>");
			scanf("%d", &c);
			int t = write(pipa[1], &c, sizeof(c));
			printf("Escribio: %d\n", t);
		}
		wait(NULL);
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
