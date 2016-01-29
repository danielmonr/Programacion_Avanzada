/*
 * =====================================================================================
 *
 *       Filename:  Ejercicio3.c
 *
 *    Description:  Ejercicio 3, Tarea-1, Programacion Avanzada,
 *    				"Hosítal"
 *
 *        Version:  1.0
 *        Created:  28/01/16 16:46:05
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

#define N 6

struct pac {
  char* nombre;
  char* apellido;
  int edad;
  int tel;
};				/* ----------  end of struct pac  ---------- */

typedef struct pac Paciente;


struct hospital {
	  Paciente* paciente;
	  int status;
};				/* ----------  end of struct hospital  ---------- */

typedef struct hospital Hospital;

typedef void(* t_funciones) (Hospital*, Paciente*, int, int);

int CamasDisp(Hospital*, int);
int CamasOcup(Hospital*, int it_h);
void ImprimirOcupadas(Hospital*, int);
void ImprimirDisponibles(Hospital*, Paciente*, int, int);
void ImprimirTodas(Hospital*, Paciente*, int, int);
void ImprimirPacientes(Hospital*,Paciente*, int, int);
void IngresarPacientes(Hospital *, Paciente *, int, int);
void AltaPaciente(Hospital *, Paciente *, int, int);
void Salir(Hospital *, Paciente *, int, int);

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
  t_funciones *menu = (t_funciones*) malloc(N * sizeof(t_funciones));
  int tam_p = 0;//tamP

  *menu = Salir;
  *(menu+1) = IngresarPacientes;
  *(menu+2) = AltaPaciente;
  *(menu+3) = ImprimirDisponibles;
  *(menu+4) = ImprimirTodas;
  *(menu+5) = ImprimirPacientes;

  int option = 1;
  int num_camas = 5;

  Paciente *p;
  Hospital *h;

  h = (Hospital *) malloc(5 * sizeof(Hospital));
  p = (Paciente *) malloc(1 * sizeof(Paciente));

  while(option > 0){
    printf("Menu:\n1. Añadir Paciente\n2. Dar de alta paciente\n3. Imprimir Camas disponibles\n4. Imprimir todas las camas\n5. Imprmir Pacientes\n0. Salir\n>>");
    scanf("%d", &option);
    if(option == 1){
      if(CamasDisp(h, num_camas) == 0){
      	num_camas += 5;
        h = (Hospital*) realloc(h, num_camas * sizeof(Hospital));
        printf("Se añadieron Camas\n");
      }

      tam_p++;
      p = (Paciente *) realloc(p, tam_p * sizeof(Paciente));
      (*(menu+option))(h, p, num_camas, tam_p-1);
    }
    else
      (*(menu+option))(h, p, num_camas, tam_p);
  }
  free(menu);
  return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

int CamasDisp(Hospital *h, int it_h){
	int i;
	int cont = 0;
	for(i = 0; i < it_h; ++i)
    if((h+i)->status == 0)
      cont++;
  	return cont;
}

int CamasOcup(Hospital *h, int it_h){
	int i;
	int cont = 0;
	for (i = 0; i < it_h; ++i){
		if ((h+i)->status == 1)
			cont++;
	}
	return cont;
}

void ImprimirOcupadas(Hospital *h, int it_h){
	printf("Camas Ocupadas:\n");
	int i;
	for (i = 0; i < it_h; ++i){
		if ((h+i)->status == 1)
			printf("Cama %d)   Paciente: %s %s Edad: %d Tel: %d\n", i+1, (h+i)->paciente->nombre, (h+i)->paciente->apellido, (h+i)->paciente->edad, (h+i)->paciente->tel);
	}
}

void ImprimirDisponibles(Hospital *h, Paciente *p, int it_h, int it_p){
	printf("Camas Desocupadas:\n");
	int i;
	for (i = 0; i < it_h; ++i){
		if ((h+i)->status == 0)
			printf("Cama %d) Desocupada\n", i+1);
	}
}

void ImprimirTodas(Hospital *h, Paciente *p, int it_h, int it_p){
	ImprimirOcupadas(h,it_h);
	ImprimirDisponibles(h,p,it_h,it_p);
}

void ImprimirPacientes(Hospital *h,Paciente* p, int it_h, int it_p){
	int i;
	printf ("--------Pacientes--------\n");
	for(i = 0; i < it_h; ++i){
		if((h+i)->status == 1)
			printf("Paciente:%s %s  Edad:%d  Telefono:%d  Cama:%d\n", (h+i)->paciente->nombre, (h+i)->paciente->apellido, (h+i)->paciente->edad, (h+i)->paciente->tel, i+1);
	}
}

void IngresarPacientes(Hospital *h, Paciente *p, int it_h, int it_p){
	printf("-----Ingreso de paciente----\n");
	int b_id;
	(p+it_p)->nombre = malloc(25 * sizeof(char));
	printf("Nombre: ");
  	scanf("%s", (p+it_p)->nombre);
  	(p+it_p)->apellido = malloc(25 * sizeof(char));
  	printf("Apellido: ");
  	scanf("%s", (p+it_p)->apellido);
  	printf("Edad: ");
  	scanf("%d", &((p+it_p)->edad));
  	printf("Telefono: ");
  	scanf("%d", &((p+it_p)->tel));

  	int disp = 1;
  	while(disp != 0){
    	ImprimirDisponibles(h, p, it_h, it_p);
    	printf("ID de la cama: ");
    	scanf("%d", &b_id);
    	b_id--;
    	if(b_id <= it_h && (h+b_id)->status == 0){
      		(h+b_id)->paciente = malloc(25 * sizeof(Paciente));
      		*(h+b_id)->paciente = *(p+it_p);
      		(h+b_id)->status = 1;
      		if((h+b_id)->status == 1)
        		disp = 0;
    	}
    	else
      		printf("Cama ocupada o no existe.\n");
  	}
}

void AltaPaciente(Hospital *h, Paciente *p, int it_h, int it_p){
  int disp = 1;
  int input;
  
  if(CamasOcup(h, it_h) > 0){
    while(disp != 0){
      ImprimirOcupadas(h, it_h);
      printf("Cama a desocupar: ");
      scanf("%d", &input);
      input--;
      if(input <= it_h && (h+input)->status==1){
        (h+input)->status = 0;
        if((h+input)->status == 0){
          disp = 0;
        }
      }
      else
        printf("Opcion no valida.\n");
    }
  }
  else
    printf("No hay pacientes.\n");
}

void Salir(Hospital *h, Paciente *p, int it_h, int it_p){
  Hospital *temp_h;
  Hospital *u_h = h+it_h;
  Paciente *temp_p;
  Paciente *u_p = p+it_p;
   
  for(temp_h = h; temp_h < u_h-1; ++temp_h){
	  if (temp_h->paciente != NULL)
   		 free(temp_h->paciente);
  }
  
  for(temp_p = p; temp_p < u_p-1; ++temp_p){
    free(temp_p->nombre);
    free(temp_p->apellido);
  }
  free(h);
  free(p);
}
