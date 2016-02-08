/*
 * =====================================================================================
 *
 *       Filename:  ejercicio2.c
 *
 *    Description:  Escriba un programa en C que calcule la integral de una función dividiendo el intervalo
 *    en 2 y generando 2 hijos. Cada hijo calcula la integral en el intervalo que se le asigna y
 *    le retorna al padre el resultado. El padre suma los resultados e imprime el valor de la
 *    integral. 
 *
 *        Version:  1.0
 *        Created:  04/02/16 10:03:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *   
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>
#include    <unistd.h>
#include    <time.h>
#include    <wait.h>

#define N 8

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	int* arr = (int *) malloc ( N * sizeof(int));
	int i;
	int estado1, estado2;
	srand((int) time(NULL));
	int r= 0;

	for (i = 0; i < N; ++i){
		*(arr+i) = rand() % 10;
		printf("n%d: %d\n", i, *(arr+i));
	}

	pid_t p;
	p = fork();
	if (p == -1){
		printf("Error al crear hijo\n");
	}
	else if ( p == 0){
		int j;
		int suma = 0;
		for (j = 0; j < N/2; ++j){
			suma += *(arr+j);
			printf("Arreglo%d: %d\n", j, *(arr+j));
		}
		printf("Suma en hijo: %d\n", suma);
		free(arr);
		exit(suma);
	}
	else{

		wait(NULL);
		if (waitpid(p, &estado1, 0) != -1){
			if (WIFEXITED(estado1)){
				printf("Salio correcto con: %d\n", estado1);
				r += WEXITSTATUS(estado1);
			}
		}

		printf("R: %d\n", r);
	
		pid_t pid;
		pid = fork();
		if (pid == -1){
			printf("Error al crear hijo\n");
		}
		else if ( pid == 0){
			int j;
			int suma = 0;
			for (j = N/2; j < N; ++j){
				suma += *(arr+j);
			}
			free(arr);
			printf("Suma en hijo2: %d\n", suma);
			//sleep(5);
			exit(suma);
		}
		wait(NULL);
	
		if (waitpid(pid, &estado2, 0) != -1){
			if (WIFEXITED(estado2)){
				r += WEXITSTATUS(estado2);
				printf ("Salio correctamente del hijo2 con: %d\n", estado2);
			}
		}
	
		printf("Suma: %d\n", r);
		free (arr);
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
