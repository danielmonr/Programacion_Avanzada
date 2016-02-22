#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define TCP_PORT 8000

int factorial (int num);

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char c;
    
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
    
    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}



int main(int argc, const char * argv[]) {

	srand((int) time(NULL));

	int * arreglo;
	int cont = 0;
	int i;
	int bool = 0;
	int max, min, prom;
    
    struct sockaddr_in direccion;
    int buffer = 1;
    
    int servidor, cliente;
    
    int leidos, escritos;
    
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    servidor = socket(PF_INET, SOCK_STREAM, 0);
    
    // Enlace con el socket
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);
    
    bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Escuchar a los clientes
    listen(servidor, 10);
    
    // Comunicación
    socklen_t tamano = sizeof(direccion);
    
    cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);
    
    int fact;
    
    if (cliente >= 0) {
        printf("Aceptando conexiones en %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        while (leidos = read(cliente, &cont, sizeof(int))) {
			arreglo = (int*) malloc (cont * sizeof(int));
			leidos = read(cliente, arreglo, cont * sizeof(int));
			max = min = *(arreglo);
			prom = 0;

			for(i = 0;i < cont; ++i){
				printf("n%d = %d\n", i, *(arreglo+i));
				if (*(arreglo+i) != 0)
					bool = 1;

				if (max < *(arreglo+i))
					max = *(arreglo+i);
				if (min > *(arreglo+i))
					min = *(arreglo+i);

				prom += *(arreglo+i);
			}

			printf("El maximo es %d, el minimo es %d, el promedio es %d\n", min, max, prom/cont);
            
            free(arreglo);
			if (bool == 0)
				break;

			bool = 0;
            
        }
    }
    
    // Cerrar el socket
    
    close(servidor);
    close(cliente);
    
    return 0;
}

