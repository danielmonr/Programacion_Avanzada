/*
 * =====================================================================================
 *
 *       Filename:  ordenamiento-generico.c
 *
 *    Description:  Algoritmos de ordenamiento en C, utilizando progra generica
 *
 *        Version:  1.0
 *        Created:  18/01/16 10:58:47
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

#define N 3

typedef enum Bool {true, false}bool;
typedef union Tipo {
	int i;
	float f;
	char c;} tipo;

typedef bool (*t_compara)(void*, void*, tipo);
typedef void (*t_algoritmo)(void*, int, tipo, t_compara);
typedef void (*t_swap)(void *, void *); 

void ordenamientoBurbuja(void*, int, tipo, bool (*) (void*, void*, tipo));
void ordenamientoInsercion(void*, int, tipo,  bool (*) (void*, void*, tipo));
void ordenamientoSeleccion(void*, int, tipo, bool (*) (void*, void*, tipo));

bool asc(void*, void*, tipo);
bool des(void*, void*, tipo);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){

	t_algoritmo * alg = (t_algoritmo *) malloc (N * sizeof(t_algoritmo));
	*alg = ordenamientoBurbuja;
	*(alg+1) = ordenamientoInsercion;
	*(alg+2) = ordenamientoSeleccion;

	t_compara * comp = (t_compara *) malloc (2 * sizeof(t_compara));
	*comp = asc;
	*(comp+1) = des;

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

bool asc(void* i, void* j, tipo t){
	bool b = ((*i)(t) > (*j)(t));
	return b;
}

bool des(void* i, void* j, tipo t){
	return *i(t) < *j(t);
}


void ordenamientoBurbuja(void* v, int n, tipo t, bool compara (void*, void*, tipo)){
	
}

void ordenamientoInsercion(void* v, int n, tipo t,  bool compara (void*, void*, tipo)){

}

void ordenamientoSeleccion(void* v, int n, tipo t, bool compara (void*, void*, tipo)){

}
