/*
 * =====================================================================================
 *
 *       Filename:  ejercicio3.c
 *
 *    Description:  Escriba un programa en C que pida la cantidad de procesos hijos a crear, el proceso
 *    principal creará inicialmente todos los hijos, cada hijo esperará un tiempo aleatorio y
 *    luego el padre esperará a que cada hijo termine y según estos van terminando, el padre
 *    imprimirá el PID del hijo. 
 *
 *        Version:  1.0
 *        Created:  04/02/16 10:04:54
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
#include    <time.h>
#include    <wait.h>

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){

	int num;
	printf("Cuantos procesos hijos: ");
	scanf("%d", &num);
	pid_t* pid = (pid_t *) malloc (num* sizeof(pid_t));

	int i;
	for (i = 0; i < num; ++i){
		*(pid+i) = fork();
		if (*(pid+i) == -1){
			printf ("Error al crear hijo\n");
		}
		else if (*(pid+i) == 0){
			srand( (int) time (NULL)^(getpid()<<1));
			int r = rand() %5;
			printf("Hijo de: %d\tcon PID: %d\tespera: %d\n", getppid(), getpid(), r);
			sleep(r);
			return 0;
		}
	}

	pid_t pt;
	while ((pt = wait(NULL)) > 0)
		printf("Termino el proceso: %d\n", pt);

	printf ("termino\n");
	free(pid);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
