/*
 * =====================================================================================
 *
 *       Filename:  factorial_fifo_write.c
 *
 *    Description:  escribe
 *
 *        Version:  1.0
 *        Created:  08/02/16 11:23:59
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
#include    <sys/stat.h>
#include    <fcntl.h>
#include    <errno.h>

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int  err;

	err = mkfifo("home/daniel/Documents/Tec/6°/Programacion_Avanzada/ipc/fifo", 0777);

	if (err){
		int errsv = errno;
		if (errsv == EACCES){
			printf("no hay acceso\n");
		}
		else if(errsv == EEXIST){
			printf("Existe\n");
		}
		else if (errsv == ELOOP){
			printf("LOOP\n");
		}
		printf("Error al crear fifo %d\n", errsv);
		exit(-1);

	}

	int fd;
	fd = open("~/Documents/Tec/6°/Programacion_Avanzada/ipc/fifo", O_WRONLY);
	int c = -1;

	while( c != 0){
		printf(">>");
		scanf("%d", &c);
		write(fd, &c, sizeof(int));
	}

	close(fd);
	unlink("~/Documents/Tec/6°/Programacion_Avanzada/ipc/fifo");

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
