/*
 * =====================================================================================
 *
 *       Filename:  concurrencia.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  17/03/16 10:22:09
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
#include    <unistd.h>
#include    <pthread.h>
#include    <time.h>
#include    <semaphore.h>

#define C_generales 5
#define C_empresariales 3

struct empresarial {
	sem_t sem;
	int id;
	int cont;
	int id_u;

};				/* ----------  end of struct empresarial  ---------- */

typedef struct empresarial Empresarial;


struct general {
	sem_t sem;
	int id;
	int cont;
	int id_u;
};				/* ----------  end of struct general  ---------- */

typedef struct general General;

Empresarial cajeros_emp[C_empresariales];
Empresarial cajeros_gen[C_generales];

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	srand((unsigned)time(NULL));

	int i = 0;


	for (i; i < C_empresariales; ++i){
		sem_init(&(cajeros_emp[i].sem), 0, 1);
		cajeros_emp[i].id = i;
		cajeros_emp[i].cont = 0;
	}

	for (i = 0; i < C_generales; +i){
		sem_init(&(cajeros_gen[i].sem), 0, 1);
		cajeros_gen[i].id = i;
		cajeros_gen[i].cont = 0;
	}

	pthread_t usuarios_gen[100];
	pthread_t usuarios_emp[50];



	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* realizarOpEmp(int n){
	int status = -1;
	int i = 0;
	while(status == -1){
		for (i; i < C_empresariales; ++i){
			status = sem_trywait(cajeros_emp[i].sem);
			if (status == 0)
				atenderEmpresarial(n, i);
		}
	}
}

void* atenderEmpresarial(int n, int p){
	printf("Se esta atendiendo al cliente %d, en el cajero E%d.\n", n, p);
	cajeros_emp[p].cont += 1;

	sleep((rand() % 120) +180);

	if(cajeros_emp[p].cont == 5){
		sleep(180);
		cont = 0;
	}
	pthread_exit(NULL);
}

void* atenderGeneral(int n, int p){
	printf("Se esta atendiendo al cliente %d, en el cajero G%d.\n", n, p);
	cajeros_gen[p].cont += 1;

	sleep((rand() % 120) +180);

	if(cajeros_gen[p].cont == 5){
		sleep(180);
		cont = 0;
	}

	pthread_exit(NULL);
}
