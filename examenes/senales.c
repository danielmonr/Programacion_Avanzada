/*
 * =====================================================================================
 *
 *       Filename:  ejercicio1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/03/16 13:44:33
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
#include    <signal.h>
#include    <wait.h>
#include    <sys/types.h>

int h;
int x = 0;
int y = 0;
int t = 3;

void mUSR(int);
void manejador(int);
void manejador_alarma(int);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	pid_t pid;
	int status;

	struct sigaction act;

	pid = fork();
	h = pid;

	if(pid < 0){
		printf("Error al crear el hijo.\n");
		exit(-1);
	}
	else if(pid == 0){
		printf("Soy el hijo %d\n", getpid());
		signal (SIGINT, SIG_IGN);
		signal (SIGTSTP, SIG_IGN);
		sleep(10);
		//printf("Desperte\n");
		kill(getppid(), SIGUSR1);
	}
	else{
		printf("Soy el padre %d\n", getpid());

		act.sa_handler = manejador;
		act.sa_flags = SA_RESTART;
		sigaction (SIGINT, &act, 0);

		act.sa_handler = manejador;
		act.sa_flags = SA_RESTART;
		sigaction(SIGTSTP, &act, 0);

		act.sa_handler = mUSR;
		act.sa_flags = SA_RESTART;
		sigaction (SIGUSR1, &act, 0);
		/*
		signal(SIGINT, manejador);
		signal(SIGTSTP, manejador);
		signal(SIGUSR1, mUSR);
		*/

		act.sa_handler = manejador_alarma;
		act.sa_flags = SA_RESTART;

		sigaction (SIGALRM, &act, 0);

		alarm(t);

		if (waitpid(pid, &status, 0) != -1)
			wait(NULL);

	}


	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void mUSR(int sig){
	printf("Se ha pulsado %d veces CTRL+C y se ha pulsado %d veces CTRL+Z. Acabando...\n",x,y);
	signal(SIGKILL, SIG_DFL);
	raise(SIGKILL);
}

void manejador(int sig){
	//printf("Entro el manejador %d\n", getpid());
	if (sig == SIGINT){
		//printf("Entro c...\n");
		x++;
		t++;
	}
	else if(sig == SIGTSTP){
		//printf("Entro z...\n");
		y++;
		if (t > 1)
			t--;
	}
}

void manejador_alarma(int sig){
	printf("Aparezco cada %d, segundos.\n", t);
	alarm(t);
}
