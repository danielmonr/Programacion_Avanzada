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

#define C_generales 5
#define C_empresariales 3

sem_t sem_emp[C_empresariales];
sem_t sem_gen[C_generales];


struct empresarial {
	int id;
	int cont;
	int id_u;

};				/* ----------  end of struct empresarial  ---------- */

typedef struct empresarial Empresarial;


struct general {
	int id;
	int cont;
	int id_u;
};				/* ----------  end of struct general  ---------- */

typedef struct general General;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	srand((unsigned)time(NULL));

	int i = 0;

	Empresarial cajeros_emp[C_empresariales];
	Empresarial cajeros_gen[C_generales];

	for (i; i < C_empresariales; ++i){
		sem_init(&sem_emp[i], 0, 1);
		cajeros_emp[i].id = i;
		cajeros_emp[i].cont = 0;
	}

	for (i = 0; i < C_generales; +i){
		sem_init(&sem_gen[i], 0, 1);
		cajeros_gen[i].id = i;
		cajeros_gen[i].cont = 0;
	}

	pthread_t usuarios_gen[100];
	pthread_t usuarios_emp[50];



	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* atenderEmpresarial(void* p){


	Empresarial* e = (Empresarial*)p;
	if(e->cont == 5){
		sleep(180);
	}
	pthread_exit(NULL);
}

void* atenderGeneral(void* p){
	General* g = (General*)p;

	if(g->cont == 5){
		sleep(180);
	}
	pthread_exit(NULL);
}
