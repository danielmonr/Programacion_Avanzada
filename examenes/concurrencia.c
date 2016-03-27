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


struct persona {
	struct persona* previa;
	sem_t espera;
};				/* ----------  end of struct persona  ---------- */

typedef struct persona Persona;

Empresarial cajeros_emp[C_empresariales];
Empresarial cajeros_gen[C_generales];
Persona empresarios[50];
Persona generales[100];

void* filaGeneral(int);
void* filaEmpresarial(int);
void* realizarOpEmp(int);
void* realizarOpGen(int);
void* atenderGeneral(int, int);
void* atenderEmpresarial(int, int);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	srand((unsigned)time(NULL));

	int i = 0;

	for (i; i < C_empresariales; ++i){
		sem_init(&(cajeros_emp[i].sem), 0, 1);
		cajeros_emp[i].id = i;
		cajeros_emp[i].cont = 0;
	}

	for (i = 0; i < C_generales; ++i){
		sem_init(&(cajeros_gen[i].sem), 0, 1);
		cajeros_gen[i].id = i;
		cajeros_gen[i].cont = 0;
	}

	pthread_t usuarios_gen[100];
	pthread_t usuarios_emp[50];

	Persona* temp = NULL;
	for (i = 0; i < 100; ++i){
		sem_init(&(generales[i].espera), 0, 0);
		generales[i].previa = temp;
		temp = &(generales[i]);
	}

	temp = NULL;
	for (i = 0; i < 50; ++i){
		sem_init(&(empresarios[i].espera), 0, 0);
		empresarios[i].previa = temp;
		temp = &(empresarios[i]);
	}

	pthread_t * aux;

	int indice = 0;
	for (aux = usuarios_emp; aux < (usuarios_emp + 50); ++aux){
		pthread_create(aux, NULL, filaEmpresarial, (void*) indice++);
		sleep((rand()%170) + 50);
	}
	for (aux = usuarios_gen; aux < (usuarios_gen + 100); ++aux){
		pthread_create(aux, NULL, filaGeneral, (void*) indice++);
		sleep((rand()%250)+90);
	}

	for (aux = usuarios_emp; aux < (usuarios_emp +50); ++aux){
		pthread_join(*aux, NULL);
	}
	for(aux = usuarios_gen; aux < (usuarios_gen +100); ++aux){
		pthread_join(*aux, NULL);
	}

	for (i =0; i < C_generales; ++i){
		sem_destroy(&(cajeros_gen[i].sem));
	}
	for (i = 0; i< C_empresariales; ++i){
		sem_destroy(&(cajeros_emp[i].sem));
	}
	for (i = 0; i < 50; ++i){
		sem_destroy(&(empresarios[i].espera));
	}
	for (i = 0;i <100; ++i){
		sem_destroy(&(generales[i].espera));
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* filaEmpresarial(int n){
	if (empresarios[n].previa != NULL){
		printf("Esperando en la fila, e%d\n", n);
		sem_wait(&(empresarios[n].previa->espera));
	}
	sem_post(&(empresarios[n].espera));
	return realizarOpEmp(n);
}

void* filaGeneral(int n){
	if(generales[n].previa != NULL){
		printf("Esperando en la fila, g%d\n", n);
		sem_wait(&(generales[n].previa->espera));
	}
	sem_post(&(generales[n].espera));
	return realizarOpGen(n);
}

void* realizarOpEmp(int n){
	int status = -1;
	int i = 0;
	while(status == -1){
		for (i; i < C_empresariales; ++i){
			status = sem_trywait(&(cajeros_emp[i].sem));
			if (status == 0)
				atenderEmpresarial(n, i);
		}
	}
}


void* realizarOpGen(int n){
	int status = -1;
	while(status == -1){
		int i = 0;
		for (i; i < C_generales; ++i){
			status = sem_trywait(&(cajeros_gen[i].sem));
			if (status == 0)
				atenderGeneral(n,i);
		}
		for (i = 0; i < C_empresariales; ++i){
			status = sem_trywait(&(cajeros_emp[i].sem));
			if (status == 0)
				atenderEmpresarial(n, i);
		}
	}
}

void* atenderEmpresarial(int n, int p){
	printf("Se esta atendiendo al cliente %d, en el cajero E%d.\n", n, p);
	cajeros_emp[p].cont += 1;

	sleep((rand() % 120) +180);
	//sleep(5);

	if(cajeros_emp[p].cont == 5){
		sleep(180);
		cajeros_emp[p].cont = 0;
	}
	sem_post(&(cajeros_emp[p].sem));
	pthread_exit(NULL);
}

void* atenderGeneral(int n, int p){
	printf("Se esta atendiendo al cliente %d, en el cajero G%d.\n", n, p);
	cajeros_gen[p].cont += 1;

	sleep((rand() % 120) +180);
	//sleep(5);

	if(cajeros_gen[p].cont == 5){
		sleep(180);
		cajeros_gen[p].cont = 0;
	}

	sem_post(&(cajeros_gen[p].sem));
	pthread_exit(NULL);
}
