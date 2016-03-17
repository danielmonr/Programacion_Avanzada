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

#define C_generales 5
#define C_empresariales 3


struct empresarial {
	int cont;

};				/* ----------  end of struct empresarial  ---------- */

typedef struct empresarial Empresarial;


struct general {
	int cont;
};				/* ----------  end of struct general  ---------- */

typedef struct general General;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	Empresarial cajeros_emp[C_empresariales];
	Empresarial cajeros_gen[C_generales];
	int i = 0;

	for (i; i < C_empresariales; ++i){
		cajeros_emp[i].cont = 0;
	}

	for (i = 0; i < C_generales; +i){
		cajeros_gen[i].cont = 0;
	}



	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void* atenderEmpresarial(void* p){
	pthread_exit(NULL);
}

void* atenderGeneral(void* p){
	pthread_exit(NULL);
}
