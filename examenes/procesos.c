/*
 * =====================================================================================
 *
 *       Filename:  procesos.c
 *
 *    Description:  Examen rapido de programación avanzada. Procesos, forks.
 *
 *        Version:  1.0
 *        Created:  08/02/16 10:01:28
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
	int n;
	if (argc != 2){
		printf("Numero de argumentos incorrecto\n");
		return 0;
	}
	else{
		n = atoi(argv[1]);
	}

	int i;
	pid_t pid;

	for (i = 0; i < n ; ++i){
		pid = fork();
		if (pid < 0 ){
			printf ("Error al crear el hijo %d, se crearon %d hijos\n", i, i-1);
			break;
		}
		else if ( pid == 0){
				int prom = getpid() + getppid();
				prom = prom / 2;
				printf ("El promedio es de %d\n", prom);
				exit(0);
		}
	}

	for (i; i > 0; --i){
		wait(NULL);
	}

	printf("Terminaron lo sprocesos hijos, el programa se cerrara\n");

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
