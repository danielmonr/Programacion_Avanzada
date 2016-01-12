/*
 * Ejercicio 1, uso de Malloc y realloc
 *
 * Owner: Daniel Monzalvo
 * Matricula: A01021514
 * Mail: danielmonr@gmail.com
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct persona{
	char nombre[10];
	char ap_pat[10];
	char ap_mat[10];
	int edad
}p;

typedef void (*funciones)();

// Funciones
void crear();
void listar();
void prom();
void joven();
void vieja();
void rango();

// Variables globales
p* lista;
int n = 0;

int main(){
	printf("Ejercicio en de lostado de personas.\n");
	printf("Daniel Monzalvo, A01021514\n\n");
	// Manual
	printf("Manual del usuario:\nEscribir un numero del 1 al 6 para seleccionar una opcion del menu, cualquier otro numero para salir.\nLas edades deben ser enteros, los nombre y apellidos deben de tener una longitud maxima de 10 caracteres.\n\n");

	// Definir arreglo de funciones
	funciones funcion[6];
	funcion[0] = crear;
	funcion[1] = listar;
	funcion[2] = prom;
	funcion[3] = joven;
	funcion[4] = vieja;
	funcion[5] = rango;

	// Menu
	while (1){
		printf("\n------------------------------Menu:-------------------------------------\n");
		printf("Crear Persona (1)\nListar Personas (2)\nEdad Promedio (3)\nPersona mas joven (4)\nPersona mas vieja(5)\nPersonas en un rango de Edad(6)\n");
		int r;
		scanf("%d",&r);
		if(r > 0 && r < 7)
			funcion[r-1]();
		else
			exit(0);
	}

}

void crear(){
	printf("\n----------------Crear----------------------\n");
	if (n == 0){
		lista = (p*) malloc (sizeof(p));
		n++;
	}
	else{
		lista = (p*) realloc(lista, sizeof(p)*n);
		n++;
	}
	printf("Nombre: ");
	scanf("%s",(lista+n-1)->nombre);
	printf("Apellido paterno: ");
	scanf("%s",(lista+n-1)->ap_pat);
	printf("Apellido materno: ");
	scanf("%s",(lista+n-1)->ap_mat);
	printf("edad: ");
	scanf("%d",&(lista+n-1)->edad);

}
void listar(){
	printf("----------------------listar-----------------------\n");
	int i;
	for (i=0; i < n; ++i){
		printf("%s %s %s\nedad: %d\n", (lista+i)->nombre, (lista+i)->ap_pat, (lista+i)->ap_mat, (lista+i)->edad);
	}
}

void prom(){
	int i;
	int promedio = 0;
	for (i=0; i < n; ++i){
		promedio  += (lista+i)->edad;
	}
	promedio = promedio / n;
	printf("\nPromedio de edad = %d\n", promedio);

}

void joven(){
	int i;
	if(n < 1)
		return;
	p* pers = lista;
	for (i = 1; i < n; i ++){
		pers = ((lista+i)->edad < pers->edad)? (lista+i) : pers;
	}
	printf("Persona mas joven: %s\n", pers->nombre);
}

void vieja(){
	int i;
	if(n < 1)
		return;
	p* pers = lista;
	for (i = 1; i < n; i ++){
		pers = ((lista+i)->edad > pers->edad)? (lista+i) : pers;
	}
	printf("Persona mas vieja: %s\n", pers->nombre);

}

void rango(){
	int i, min, max;
	if(n < 1)
		return;
	printf("--------------Por rango de edad---------------\n");
	printf("Edad minima: ");
	scanf("%d", &min);
	printf("Edad maxima: ");
	scanf("%d", &max);

	for (i = 1; i < n; i ++){
		if ((lista+i)->edad >= min && (lista+i)->edad <= max)
			printf("%s\n", (lista+i)->nombre);
	}

}

