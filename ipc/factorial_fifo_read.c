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

	fd = open("~/Documents/Tec/6°/Programacion_Avanzada/ipc/fifo", O_RDONLY);

	int r, i;
	i = -1;

	while(i != 0){
		r = 1;
		read(fd, &i, sizeof(int));
		int j;
		for (j = 2; j <= i; j++){
			r *= j;
		}
		printf("Factorial: %d\n", r);
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
