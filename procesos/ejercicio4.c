/*
 * =====================================================================================
 *
 *       Filename:  ejercicio4.c
 *
 *    Description:  Escriba un programa en C que reciba como argumentos de la línea de comandos la
 *    cantidad de niveles de procesos hijos a crear (-n) y el número de procesos por niveles (-
 *    p) , el proceso principal creará inicialmente los procesos del primer nivel y cada uno de
 *    estos crearán los procesos del segundo nivel y así sucesivamente hasta que se creen
 *    todos los procesos de todos los niveles. En cada nivel, excepto el último, cada proceso
 *    debe esperar a que se terminen sus hijos.
 *    Como salida del programa debe mostrar una jerarquía arbórea que represente la
 *    jerarquía de procesos (similar a la salida del comando pstree)
 *
 *        Version:  1.0
 *        Created:  04/02/16 10:10:26
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

void crearHijos(int, int, int);
/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){

	if (argc != 3){
		printf("Numero de argumentos incorrecto\n");
		return 0;
	}

	int n = atoi(argv[1]);
	int p = atoi(argv[2]);

	crearHijos(0, n, p);

	return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */

void crearHijos(int n, int max, int p){
	int i = 0;
	pid_t pid;
	int j = 0;
	for (j; j < n; ++j)
		printf("\t");
	printf("%d\n", getpid());
	for (i; i < p; ++i){
		pid = fork();
		if (pid < 0){
			printf("Error creando hijo\n");
			exit(-1);
		}
		if (pid == 0){
			if (n < max){
				crearHijos(n+1, max, p);
			}
			exit(0);
		}
		else{
			for (j = 0; j < p; ++j)
				wait(NULL);
		}
	}
}
