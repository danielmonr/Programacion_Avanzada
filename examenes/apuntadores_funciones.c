/*
 * =====================================================================================
 *
 *       Filename:  apuntadores_funciones.c
 *
 *    Description:  Examen Rapido, apuntadores a funciones
 *
 *        Version:  1.0
 *        Created:  28/01/16 09:57:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  ITESM, CSF
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>


enum funcion {begin, end, next, prev};				/* ----------  end of enum funcion  ---------- */

typedef enum funcion Funcion;

typedef void* (*t_ite)(void *, size_t, Funcion, int);

void Recorre(void*, t_ite, size_t);

* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	return EXIT_SUCCESS;
}

/* ----------  end of function main  ---------- */

void* it_f(void* a, size_t t, Funcion f, int c){
	switch (f){
		case 0:
			return a;
			break;
		case 1:
			return (a+(c*t));
			break;
		case 2:
			return (a+t);
			break;
		case 3:
			return (a-t);
			break;
		default:
			return a;
			break;
	}
}

void * it_

void Recorre(void* a, t_ite, size_t t){

}
