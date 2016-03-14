/*
 * =====================================================================================
 *
 *       Filename:  ejercicio2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/03/16 15:06:17
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
#include    <sys/types.h>
#include    <string.h>
#include    <dirent.h>
#include    <sys/stat.h>
#include    <signal.h>
#include    <unistd.h>
#include    <fcntl.h>

#define N 5
#define T 4

int grabar = 1;

int borrar_directorio(char*);
void gestorAlrm(int);
FILE* f;

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){

	sigset_t conjunto, pendientes;
	sigfillset(&conjunto);
	sigdelset(&conjunto, SIGALRM);
	sigprocmask(SIG_BLOCK, &conjunto, NULL);


	char* path = "./datos";
	size_t path_len = strlen(path);

	struct stat st;

	if (stat(path, &st) != -1){
		if(borrar_directorio < 0){
			printf("Error al borrar directorio.\n");
			abort();
		}
	}

	mkdir (path, 0770);

	signal(SIGALRM, gestorAlrm);
	int i = 0;
	char* nombre = (char*) malloc (4+path_len);
	int fd;

	alarm(T);

	for (i; i < N; ++i){
		snprintf(nombre, 4 + path_len, "%s/a%d",path, i);
		fd = open(nombre, O_CREAT | O_RDWR, 0666);
		if((f = fdopen(fd, "w+")) == NULL){
			printf("Error %s ", nombre);
			printf("error en %c%d\n", 'a', i);
		}
		sleep(3);
		while(grabar == 1){
			fprintf(f,"x");
		}
		sigpending(&pendientes);
		int h = 1;
		for (h; h < NSIG; ++h){
			if(sigismember(&pendientes, h))
				fprintf(f,"Pendiente: senaln°%d\n", h);
		}
		fclose(f);
		sigemptyset(&pendientes);
		grabar = 1;
	}

	i = 0;
	printf("Archivos creados:\n");
	int* tamanos = (int*) malloc (5*sizeof(int));
	for (i; i < N; ++i){
		snprintf(nombre, 4+ path_len, "%s/a%d", path, i);
		stat(nombre, &st);
		*(tamanos+i) = st.st_size;
		printf("%s tamano: %d\n", nombre, *(tamanos+i));
	}


	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

int borrar_directorio(char* path){
	char* buffer;
	DIR *direct;
	int r = -1;
	size_t path_len = strlen(path);
	struct dirent *ep;
	direct = opendir("./datos");
	if (direct != NULL){
		r = 0;
		while (ep = readdir (direct)){
			int r2 = -1;
			if (!strcmp(ep->d_name, ".") || !strcmp(ep->d_name, ".."))
				continue;

			size_t len = path_len + strlen(ep->d_name) + 2;
			buffer = (char*) malloc (len);
			if(buffer){
				struct stat statbuf;
				snprintf(buffer, len, "%s/%s", path, ep->d_name);
				if(!stat(buffer, &statbuf)){
					if(S_ISDIR(statbuf.st_mode))
						r2 = borrar_directorio(buffer);
					else
						r2 = unlink(buffer);
				}
				free(buffer);
			}
			r = r2;
		}
		closedir(direct);
	}
	if (!r)
		r = rmdir(path);

	return r;
}

void gestorAlrm(int sig){
	//printf("Entro al gestor.\n");
	grabar = 0;
	alarm(T);
}

