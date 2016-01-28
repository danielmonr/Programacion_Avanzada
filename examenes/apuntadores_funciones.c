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

struct iter {
	void* a;
	size_t t;
	int tam;
	int pos;
};				/* ----------  end of struct iter  ---------- */

typedef struct iter Iter;

typedef enum funcion Funcion;

typedef Iter (*t_ite)(Iter, size_t, Funcion, int);

Iter it_back(Iter, size_t, Funcion, int);
Iter it_bi(Iter, size_t, Funcion, int);
Iter it_f(Iter, size_t, Funcion, int);
void Recorre(Iter, t_ite, size_t, int);

* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){a
	t_ite * iteradores = (t_ite *) malloc (3 * sizeof(t_ite));
	*iteradores = it_f;
	*(iteradores+1) = it_back;
	*(iteradores+2) = it_bi;


	return EXIT_SUCCESS;
}

/* ----------  end of function main  ---------- */

Iter it_f(Iter a, size_t t, Funcion f, int c){
	switch (f){
		case 0:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;

			return a;
			break;
		case 1:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;
			return a;
			break;
		case 2:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;
			return a;
			break;
		case 3:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;
			return a;
			break;
		default:
			return a;
			break;
	}
}

Iter it_back(Iter a, size_t t, Funcion f, int c){
	switch (f){
		case 0:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;
			return a;
			break;
		case 1:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;
			return a;
			break;
		case 2:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < tam) ? a.pos + 1 : a.pos;
			return a;
			break;
		case 3:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;
			return a;
			break;
		default:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;
			return a;
			break;
	}
}

Iter it_bi(Iter a, size_t t, Funcion f, int c){
	switch (f){
		case 0:
			a.a = a.a - (a.pos*a.t);
			a.pos = (a.pos < a.tam) ? a.pos = 0 : a.pos;
			return a;
			break;
		case 1:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;
			return a;
			break;
		case 2:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;
			return a;
			break;
		case 3:
			a.a = (a.pos < a.tam) ? a.a + t : a.a;
			a.pos = (a.pos < a.tam) ? a.pos + 1 : a.pos;
			return a;
			break;
		default:
			return a;
			break;
	}
}

void Recorre(void* a, t_ite, size_t t, int tam){

}
