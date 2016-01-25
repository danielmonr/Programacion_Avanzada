/*
 * =====================================================================================
 *
 *       Filename:  apunt-funciones.c
 *
 *    Description:  Ejercicios de apuntadores a funciones
 *
 *        Version:  1.0
 *        Created:  18/01/16 10:25:42
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

typedef void (* opciones)();

void opcion1();
void opcion2();
void opcion3();

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){

	opciones * op_menu = (opciones *) malloc(N * sizeof(opciones));
	*op_menu = opcion1;
	*(op_menu+1) = opcion2;
	*(op_menu+2) = opcion3;

	int opcion = -1;
	while(opcion != 0){
		printf("1-Opcion 1\n2-Opcion 3\n3-Opcion 3\n0-Salir\n");
		printf("Selecciona tu opcion: ");
		scanf("%d", &opcion);
		if (opcion > 0 && opcion < 3)
			op_menu[opcion-1]();
	}

	free(op_menu);
	return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */

void opcion1(){
	printf("Seleccionaste la opcion 1");
}

void opcion2(){
	printf("Seleccionaste la opcion 2");
}

void opcion3(){
	printf("Seleccionaste la opcion 3");
}

