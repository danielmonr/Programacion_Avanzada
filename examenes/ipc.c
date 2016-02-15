/*
 * =====================================================================================
 *
 *       Filename:  ipc.c
 *
 *    Description:  Examen rapido de comunicacion de procesos, FIFOS y PIPES.
 *
 *        Version:  1.0
 *        Created:  15/02/16 10:00:49
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
	if(argc < 2 || argc > 2){
		printf("Numero de argumentos invalido\n");
		exit(-1);
	}
	int N = atoi(argv[1]);

	int** ps = (int**) malloc (N+1* sizeof(int*));
	int j = 0;
	for (j; j <= N; j++){
		*(ps+j) = (int) malloc (2* sizeof(int));
	}
	char c;

	pid_t pid;

	pipe(*(ps));

	char testigo = 'T';

	int i = 0;

	for (i; i< N-1; ++i){
		pid = fork();
		if (pid < 0){
			printf("Error al crear proceso\n");
			exit(-1);
		}
		if (pid == 0){
			close((*(ps+i)[1]);
			pipe(p1);
			close(p1[0]);
			read(p[0], &c, sizeof(char));
			write(p1[1], &c, sizeof(char));
		}
		else{

		}
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

int crear(int i, int m){
	int p[1];
}
