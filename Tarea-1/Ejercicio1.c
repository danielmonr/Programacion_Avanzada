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

#define N 5


struct persona {
	char* nombre;
	char* apellido_p;
	char* apellido_m;
	int edad;
	char* rol;
	int id_barco;
};				/* ----------  end of struct persona  ---------- */

typedef struct persona Persona;

struct embarcacion {
	Persona propietario;
	char* nombre;
	int eslora;
	int manga;
	int max_trip;
	int capa;
};				/* ----------  end of struct embarcacion  ---------- */

typedef struct embarcacion Embarcacion;

// Funciones
typedef void (* t_funciones)(Embarcacion*, int);
void Incorp_barcos(Embarcacion* , int);
void Incorp_trip(Embarcacion*, int);
void MostrarEmbarcacion(Embarcacion* p, int);
void MostrarTodas(Embarcacion* p, int);
void Salir(Embarcacion* p, int);

void imprimirTripulante(int t);
Persona crearP();
int igual(char*, char*);

// Variables globales
Persona* tripulantes;
int num_trip = 0;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	Embarcacion* puerto = (Embarcacion*) malloc (sizeof(Embarcacion));;
	int tam = 0;
	int op = 1;

	t_funciones * funciones = (t_funciones *) malloc (sizeof(t_funciones) * N);
	*funciones = Salir;
	*(funciones+1) = Incorp_barcos;
	*(funciones+2) = Incorp_trip;
	*(funciones+3) = MostrarEmbarcacion;
	*(funciones+4) = MostrarTodas;

	printf("Tarea-1, Ejercicio-1, Daniel Monzalvo, A01021514\n");
	printf("----------Puerto----------\n");
	while(op != 0){
		printf("1- Anadir barcos\n2- Anadir Tripulantes\n3- Imprimir una embarcacion\n4- Imprimir todas las embarcaciones\n0- Salir\n");
		scanf("%d", &op);
		if (op == 1){
			puerto = (Embarcacion *) realloc (puerto, ++tam * sizeof(Embarcacion));
		}
		if (op >= 0 && op < 5)
			(*(funciones+op))(puerto, tam);
	}

	free (funciones);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void Incorp_barcos(Embarcacion* p, int t){
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
	printf("Dueño:\n");
	ptr->propietario = crearP();
	ptr->propietario.id_barco = t;
	ptr->capa = ptr->max_trip;
}

void Incorp_trip(Embarcacion* p, int t){
	int i;
	printf("ID de la embarcacion: ");
	scanf("%d", &i);
	if (i > t){
		printf("ID incorrecto\n");
		return Incorp_trip(p, t);
	}
	if ((p+i-1)->capa < 1){
		printf("Esta embarcacion ya no tiene espacio\n");
		return;
	}

	num_trip++;
	tripulantes = (Persona *) realloc (tripulantes, num_trip * sizeof(Persona));
	(tripulantes+num_trip-1)->id_barco = i;
	(tripulantes+num_trip-1)->nombre = (char*) malloc (25);
	(tripulantes+num_trip-1)->apellido_p= (char*) malloc (25);
	(tripulantes+num_trip-1)->apellido_m= (char*) malloc (25);
	(tripulantes+num_trip-1)->rol= (char*) malloc (25);
	printf("Nombre del tripulante: ");
	scanf("%s", (tripulantes+num_trip-1)->nombre);
	printf("Apellido Paterno: ");
	scanf("%s", (tripulantes+num_trip-1)->apellido_p);
	printf("Apellido Materno: ");
	scanf("%s", (tripulantes+num_trip-1)->apellido_m);
	printf("Edad: ");
	scanf("%d", &(tripulantes+num_trip-1)->edad);
	printf("Rol: ");
	scanf("%s", (tripulantes+num_trip-1)->rol);
	(p+i-1)->capa--;
}

void MostrarEmbarcacion(Embarcacion* p, int t){
	Embarcacion *ptr = p+t-1;
	printf("\n--------Embarcacion n°%d--------\n", t);
	printf("Nombre: %s\nEslora: %d    Manga: %d\nCapacidad: %d    Disponible: %d\n", ptr->nombre, ptr->eslora, ptr->manga, ptr->max_trip, t);
	printf("-----Propietario-----\n");
	printf("Nombre: %s  Apellido P: %s Appelido M: %s\nEdad: %d\n", ptr->propietario.nombre, ptr->propietario.apellido_p, ptr->propietario.apellido_m, ptr->propietario.edad);
	printf("Tripulacion\n");
	imprimirTripulante(t);
}

void MostrarTodas(Embarcacion* p, int t){
	printf("--------Embarcaciones--------\n");
	int i;
	for (i = 0; i < t; ++i){
		MostrarEmbarcacion(p,i+1);
		printf("\n");
	}
}

void Salir(Embarcacion* p, int t){
	printf("\nSaliendo...\n");
	printf("Borrando memoria\n");
	int i;
	printf(" Borrando Barcos\n");
	for (i = 0; i < t; ++i){
		free((p+i)->nombre);
	}
	free(p);
	printf(" Borrando Tripulantes\n");
	for (i = 0; i < num_trip; ++i){
		free((tripulantes+i)->nombre);
		free((tripulantes+i)->apellido_p);
		free((tripulantes+i)->apellido_m);
		free((tripulantes+i)->rol);
	}
	free(tripulantes);
	num_trip = 0;
}

void imprimirTripulante(int t){
	int i;
	for (i = 0; i < num_trip; ++i){
		if ((tripulantes+i)->id_barco == t){
			printf("-----Tripulante-----\n");
			printf("Nombre: %s  Apellido P: %s Appelido M: %s\nEdad: %d    Rol: %s", (tripulantes+i)->nombre, (tripulantes+i)->apellido_p, (tripulantes+i)->apellido_m, (tripulantes+i)->edad, (tripulantes+i)->rol);
		}
	}
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

Persona crearP(){
	Persona p;
	p.nombre = (char*) malloc (25);
	p.apellido_p = (char*) malloc (25);
	p.apellido_m = (char*) malloc (25);
	p.rol = (char*) malloc (25);

	printf("Nombre: ");
	scanf("%s", p.nombre);
	printf("Apellido paterno: ");
	scanf("%s", p.apellido_p);
	printf("Apellido materno: ");
	scanf("%s", p.apellido_m);
	printf("Edad: ");
	scanf("%d", &p.edad);
	p.rol = "Propietario";
	return p;
}
