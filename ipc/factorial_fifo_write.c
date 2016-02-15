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
#include    <string.h>
#include    <unistd.h>
#include    <sys/stat.h>
#include    <fcntl.h>
#include    <errno.h>

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int  err;
	
	printf("Creando Fifo...\n");
	err = mkfifo("/home/daniel/Documents/Tec/6°/Programacion_Avanzada/ipc/fifo", 0777);
	printf("Fifo creado.\n");

	if (err){
		int errsv = errno;
		printf("Error al crear fifo %s\n", strerror(errno));
		exit(-1);

	}

	int fd;
	printf("Abriendo archivo...\n");
	fd = open("/home/daniel/Documents/Tec/6°/Programacion_Avanzada/ipc/fifo", O_WRONLY);

	if (fd>0)
		printf("hola\n");
	else{
		printf("adios\n");
		exit(-1);
	}

	int c = -1;

	while( c != 0){
		printf(">>");
		scanf("%d", &c);
		write(fd, &c, sizeof(int));
	}

	close(fd);
	unlink("/home/daniel/Documents/Tec/6°/Programacion_Avanzada/ipc/fifo");

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
