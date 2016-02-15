/*
 * =====================================================================================
 *
 *       Filename:  factorial_fifo.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/02/16 11:23:32
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
#include    <sys/types.h>
#include    <fcntl.h>

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int fd;

	fd = open("/home/daniel/Documents/Tec/6°/Programacion_Avanzada/ipc/fifo", O_RDONLY);

	if(fd >0)
		printf("Se abrio %d\n", fd);
	else{
		printf("error\n");
		exit(-1);
	}

	int r, i, leidos;
	i = -1;
	leidos = 1;

	while(leidos= read(fd, &i, sizeof(int))){
		printf("%d\n", i);
		 r= 1;
		if (i == 0)
			break;
		int j;
		for (j = 2; j <= i; j++){
			r *= j;
		}
		printf("Factorial: %d\n", r);
	
	}

	close(fd);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
