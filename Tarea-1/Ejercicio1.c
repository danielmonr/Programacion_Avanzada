/*
 * =====================================================================================
 *
 *       Filename:  Ejercicio1.c
 *
 *    Description:  Ejercicio1 de la Tarea-1 de Programación Avanzada,
 *    				Trabajo con estructuras y apuntadores.
 *    				"Puerto Pesquero"
 *
 *        Version:  1.0
 *        Created:  26/01/16 13:13:57
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

#define N 4


struct persona {
	char* nombre;
	char* apellido_p;
	char* apellido_m;
	int edad;
	char* rol;
};				/* ----------  end of struct persona  ---------- */

typedef struct persona Persona;

struct embarcacion {
	char* nombre;
	int eslora;
	int manga;
	int max_trip;
	Persona* tripulacion;
};				/* ----------  end of struct embarcacion  ---------- */

typedef struct embarcacion Embarcacion;

// Funciones
typedef void (* t_funciones)(Embarcacion*, int);
void Incorp_barcos(Embarcacion* , int);
void Incorp_trip(Embarcacion*, int);

int igual(char*, char*);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	Embarcacion* puerto;
	int tam = 0;

	t_funciones * funciones = (t_funciones *) malloc (sizeof(t_funciones) * N);
	*funciones = Incorp_barcos;

	free (puerto);
	free (funciones);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void Incorp_barcos(Embarcacion* p, int t){
	p = (Embarcacion *) realloc(p, ++t * sizeof(Embarcacion));
	Embarcacion* ptr = p+t-1;
	printf("Nueva Embarcacion en el puerto\n");
	(*ptr).nombre = (char*) malloc (25);
	printf("Nombre de la embarcacion: ");
	scanf("%s", (*ptr).nombre);
	printf("Eslora: ");
	scanf("%d", &(*ptr).eslora);
	printf("Manga: ");
	scanf("%d", &(*ptr).manga);
	printf("Capacidad de triuplantes: ");
	scanf("%d", &(*ptr).max_trip);
}

void Incorp_trip(Embarcacion* p, int t){
	int i;
	Embarcacion* e;
	char* temp = (char*) malloc (25);
	printf("Nombre de la embarcacion a la que desea agregar el tripulante: ");
	scanf("%s", temp);

	for (i = 0; i < t; ++i){
		if (igual(temp, (p+i)->nombre)){
			e = p+i;
			break;
		}
	}
	if (e == NULL)
		return;

}

int igual(char* f, char* t){
	char* it1 = f;
	char* it2 = t;
	if (*it1 != *it2)
		return 0;
	while (*it1 != '\0'){
		if (*it2 == '\0' || *(++it1) != *(++it2))
			return 0;
	}
	return 1;

}
