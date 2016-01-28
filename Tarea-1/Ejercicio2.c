/*
 * =====================================================================================
 *
 *       Filename:  Ejercicio2.c
 *
 *    Description:  Ejercicio 2 de la Tarea-1, Programacion Avanzada
 *    				"Encuesta"
 *
 *        Version:  1.0
 *        Created:  27/01/16 12:44:33
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
#include    <time.h>

// Numero de Personas en la encuesta
#define N 3
// Numero de preguntas y respuestas por pregunta
#define M 10
#define R 7


struct persona {
	char* nombre;
	int edad;
	int* respuestas;
};				/* ----------  end of struct persona  ---------- */

typedef struct persona Persona;

// Funciones
void addPersona(Persona*, int);
void addPregunta(char***, int);
void crearEntorno(Persona*, char***);
void responderPregunta(Persona*, int, char***, int);
void realizarEncuesta(Persona*, int,char***);
void llenarEncuesta(Persona*, char***);
void llenarEncuestaRandom(Persona*, char***);
void histograma(Persona*, char***);
void histogramaEdades(Persona*, char***);

void Borrar(Persona*, char***);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	Persona* pool = (Persona*) malloc (N * sizeof(Persona));
	char*** pregs = (char***) malloc (M * sizeof(char**));
	srand((int) time(NULL));

	crearEntorno(pool, pregs);
	int op;
	printf("Llenar encuesta manualmente? (0-NO,1-SI)");
	scanf("%d",&op);
	if(op)
		llenarEncuesta(pool,pregs);
	else
		llenarEncuestaRandom(pool, pregs);
	histograma(pool, pregs);
	histogramaEdades(pool, pregs);

	Borrar(pool, pregs);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void addPersona(Persona* p, int i){
	(p+i)->nombre = (char*) malloc (25);
	printf("Nombre: ");
	scanf("%s", (p+i)->nombre);
	int d = 0;
	while (d > 120 || d < 17){
		printf("Edad: ");
		scanf("%d", &d);
		if (d < 17)
			printf("Muy joven\n");
		else if (d > 120)
			printf("Muy viejo");
		else
			(p+i)->edad = d;
	}
	(p+i)->respuestas = (int *) malloc (M * sizeof(int));
}

void addPregunta(char*** p, int i){
	*(p+i) = (char**) malloc (R * sizeof(char*));
	int j;
	*(*(p+i)) = (char*) malloc (25);
	printf("Encabezado: ");
	scanf("%s", *(*(p+i)));
	for (j = 1; j < R; ++j){
		printf("Opcion -%d", j);
		*(*(p+i)+j) = (char *) malloc (25);
		scanf("%s", (*(*(p+i)+j)));
	}
}

void crearEntorno(Persona* p, char*** e){
	int i;
	printf("Creando entorno de la Entrevista...\n");
	printf("----------Crear personas----------\n");
	for (i = 0; i < N; i++)
		addPersona(p,i);
	printf("----------Crear preguntas----------\n");
	for (i = 0; i < M; i++)
		addPregunta(e,i);
	printf("\nEntorno Creado\n");
}

void responderPregunta(Persona* p, int p_it, char*** e, int e_it){
	printf(" -Pregunta %d", e_it);
	int i;
	printf("  %s\n  Respuestas: (0 para saltar pregunta)\n", *(*(e+e_it)));
	for (i = 1; i < R; ++i){
		printf("   %d)%s", i, *(*(e+e_it)+i));
	}
	printf("    >>");
	scanf("%d", ((p+p_it)->respuestas+e_it));
}

void realizarEncuesta(Persona *p, int i, char*** e){
	int it;
	for (it = 0; it < M; ++it)
		responderPregunta(p,i,e,it);
}

void llenarEncuesta(Persona* p, char*** e){
	int i;
	for (i = 0; i < N; ++i)
		realizarEncuesta(p,i,e);
}
void llenarEncuestaRandom(Persona* p, char*** e){
	time_t t;
	int i, j;

	for (i = 0; i < N; ++i){
		for(j = 0; j < M; ++j){
			*((p+i)->respuestas+j) = rand() % 6;
		}
	}
}

void histograma(Persona* p, char*** e){
	int i,j,k;
	int cont = 0;
	int* conts = (int *) malloc (R * sizeof(int));
	for (i = 0; i < R; ++i)
		*(conts+i) = 0;

	printf("\n----------Resultados----------\n");
	printf("------Respuesta a las preguntas------\n");
	printf("Pregunta  Frecuencia\n");
	for (i = 0; i < M; i++){
		for (j = 0; j < N; ++j){
			cont = ((*(p+j)->respuestas+M) == 0) ? cont : cont++;
		}
		printf("    %d    ", i);
		for ( j = 0; j < cont; ++j)
			printf("*");
		printf("\n");
		cont = 0;
	}
	printf("\n\nFrecuencia de Respuestas\n");
	for ( i = 0; i < M; ++i){
		for(j = 0; j < N; ++j){
			(*(conts+((*(p+j)->respuestas+M))))++;
		}
		printf("Pregunta %d\n", i);
		printf("No  Respuesta Frecuencia\n");
		for (j = 1; j < R; ++j){
			printf(" %d     %d    ", j,*(conts+j));
			for (k = 0; k < *(conts+j); k++)
				printf("*");
			printf("\n");
		}
		for (j = 0; j < R; ++j)
			*(conts+j) = 0;
		printf("\n");
	}
	free(conts);
}

void histogramaEdades(Persona* p, char***e){
	int * cont = (int*) malloc (5 * sizeof(int));
	int i, j, k;
	printf("----Histograma por edades----\n");
	for (i = 0; i < M; ++i){
		printf("Pregunta %d\n", i);
		printf("No [18-25] [26-35] [36-45] [46-65] [66-120]\n");
		for(j = 1; j < R; ++j){
			printf("%d  ", j); 
			for(k = 0; k < N; ++k){
				if(*((p+k)->respuestas+i) == j){
					if ((p+k)->edad < 26)
						*cont = *cont +1;
					else if((p+k)->edad < 36)
						*(cont+1) = *(cont+1) +1;
					else if((p+k)->edad < 46)
						*(cont+2) = *(cont+2) +1;
					else if((p+k)->edad < 66)
						*(cont+3) = *(cont+3) +1;
					else if((p+k)->edad < 120)
						*(cont+4) = *(cont+4) +1;
				}
			}
			printf("   %d       %d       %d       %d       %d\n",*cont, *(cont+1), *(cont+2), *(cont+3), *(cont+4));
			for (k = 0; k < 5; k++){
				*(cont+k) = 0;
			}
		}
	}

	free (cont);
}

void Borrar(Persona* p, char*** q){
	int i,j;
	for (i = 0; i < N; ++i){
		free ((p+i)->nombre);
		free ((p+i)->respuestas);
	}
	free(p);
	for (i = 0; i < M; ++i){
		for(j = 0; j < R; ++j){
			free(*(*(q+i)+j));
		}
		free(*(q+i));
	}
	free(q);
}
