/*
 * =====================================================================================
 *
 *       Filename:  ejercicio5.c
 *
 *    Description:  Escriba un programa en C que reciba como parámetros el programa a arrancar (-p) y el
 *    número de veces (-n):
 *    Ej.- $lanzador -n 4 -p programa
 *    1/2
 *    Lanzará simultáneamente n procesos con el programa indicado y esperará por la
 *    terminación de todos sus hijos. 
 *
 *        Version:  1.0
 *        Created:  11/02/16 12:08:37
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
#include    <ctype.h>

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int n = 0;

	char* prog;
	char* arg[10] ;
	int c;
	int it = it;

	if (argc < 2){
		printf("Error, numero de argumentos no valido.\n");
	}

	opterr = 0;

while((c = getopt (argc, argv, "n:p:")) != -1)
		switch (c){
			case 'n':
				n = atoi(optarg);
				break;
			case 'p':
				prog = optarg;
				arg[0] = (char*)optarg;
				break;
			case '?':
				if (optopt == 'n' || optopt == 'p'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
					return 1;
				}
				else if(isprint (optopt)){
					char n = (char) optopt;
					char temp[3] = {'-',optopt, '\0'};
					arg[++it] = temp;
				}
				break;
			default:
				abort();
		}

	arg[++it] = NULL;
	int i = 0;
	pid_t pid;
	const char* p = prog;


	printf("Correr %s, %d veces.\n", p, n);
	for (i; i < n; ++i){
		pid = fork();
		if (pid < 0){
			printf("Error al crear proceso hijo.\n");
			exit(-1);
		}
		else if(pid == 0){
			//printf ("corriendo %s, %d veces\n", p, n);
			execvp(p, arg);
		}
	}

	for (i = 0; i < n; ++i){
		wait(NULL);
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
