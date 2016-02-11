/*
 * =====================================================================================
 *
 *       Filename:  ejercicio3.c
 *
 *    Description:  Modifique el ejercicio 1 para que el hijo no imprima el factorial, sino que en su lugar,
 *    utilizando otro pipe, se lo comunique al padre y sea este quien imprima los resultados.
 *
 *        Version:  1.0
 *        Created:  11/02/16 10:39:29
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

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int p1[2];
	int p2[2];

	pipe(p1);
	pipe(p2);

	pid_t pid = fork();

	if (pid < 0){
		printf("Error creando hijo\n");
		return 0;
	}
	else if(pid == 0){
		close(p1[0]);
		close(p2[1]);
		int c, r, i;
		c = -1;
		while(c != 0){
			r = 1;
			read(p2[0], &c, sizeof(int));
			for (i = 2; i <= c; i++){
				r *= i;
			}
			write(p1[1], &r, sizeof(int));
		}
	}
	else{
		close(p1[1]);
		close(p2[0]);

		int c = -1;
		int r;

		while( c != 0){
			printf(">>");
			scanf("%d", &c);
			write(p2[1], &c, sizeof(int));
			read(p1[0], &r, sizeof(int));
			printf("Factorial: %d\n", r);
		}
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
