/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/01/16 10:45:42
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

* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){


	while ((c = getopt (argc, argv, "abc:")) != -1){
		switch(c)
		{
			case 'a':
				aflag = 1;
				bbreak;
			case 'b':
				bflag = 1;
				break;
			case 'c':
				cvalue = optarg;
				break;
			case '?':
				if (optopt = 'c')
					fprint(stderr, "Option -%c requiere un argumento.\n", optopt);
				else if (isprint (optopt))
						fprint(stderr, "Opcion desconocida '-%c'.\n", optopt);
				else
					fprint (stderr, "Opcino desconocida.\n");
			default:
					abort ();
		}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


