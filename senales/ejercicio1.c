/*
 * =====================================================================================
 *
 *       Filename:  ejercicio1.c
 *
 *    Description: rear un proceso hijo, el cual ignorará la pulsación
 *    CTRL+C y a continuación:
 *    se pondrá a dormir 2 segundos, dará un mensaje
 *    indicando su PID y el de su padre, y contará desde 10
 *    hasta 1, a intervalos de 1 segundo
 *    Antes de terminar, dará un mensaje similar al antes
 *    mencionado
 *    Por su parte, el padre indicará su PID y advertirá que
 *    si se pulsa CTRL+C sólo morirá el padre. A
 *    continuación se pondrá a dormir 10 segundos, y
 *    finalmente, esperará a que el hijo termine, si es que
 *    no ha terminado aún
 *    Tanto el padre como el hijo ignorarán la pulsación
 *    de CTRL+Z 
 *
 *        Version:  1.0
 *        Created:  25/02/16 10:26:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <signal.h>
#include	<stdlib.h>
#include    <stdio.h>

void manejador(int);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){


	signal(SIGTSTP, SIG_IGN);

	pid_t pid = fork();

	if (pid < 0){
		printf("Error al crear hijo\n");
		abort();
	}
	else if(pid == 0){
		if (signal (SIGINT, manejador) == SIG_ERR){
			printf("Error al manejar una señal\n");
			exit(-1);
		}

		sleep(10);
		exit(0);
	}
	else{
		printf("MI pid es %d\n", getpid());
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void manejador(int s){
	sleep(2);
	printf("Mi PID es %d, el de mi padre es %d\n", getpid(), getppid());

	int i = 10;
	for (i; i > 0; --1){
		printf("%d\n", i);
		sleep (1);
	}

	printf("Mi PID es %d, el de mi padre es %d\n", getpid(), getppid());

}
