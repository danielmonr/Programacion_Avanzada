#include <stdlib.h>
#include <stdio.h>

#define N 25

char* ejercicio1(char*);
void ejercicio4();

int main(){
	/*printf("Ejercicio1\n");
	char* temp = (char*) malloc(sizeof(char) * N);
	scanf("%[^\n]s", temp);
	char* r = ejercicio1(temp);
	printf("%s", r);
	free (temp);
	free (r);*/
	ejercicio4();
}

char* ejercicio1(char* or){
	char* nv;
	char* pt;
	pt = or;
	int n = 0;
	int i;

	while(*pt != '\0'){
		n++;
		pt++;
	}
	nv = (char*) malloc(sizeof(char) * n);
	pt = nv;
	for (i = 0; i < n; i++){
		*(pt) = *(or+n-1-i);
		pt++;
	}

	return nv;
}

void ejercicio4(){
	printf("N: ");
	int n, m;
	scanf("%d", &n);
	printf("M: ");
	scanf("%d", &m);
	int* matriz = (int*) malloc(sizeof(int) * (m*n));
	int* ptr = matriz;
	int i;
	for (i = 0; i < n*m; ++i){
		int _n = i / n;
		int _m = i % n;
		printf("Inserte valor[%d][%d]: ", _n, _m);
		scanf("%d", ptr++);
	}

	printf("Imprimir matriz: \n");
	i = 0;
	for (ptr = matriz; ptr < (matriz+(n*m)); ptr++){
		if((i %n) == 0)
			printf('\n');

		printf ("%d ", *ptr);
	}

	free(matriz);
}
