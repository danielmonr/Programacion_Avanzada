ALL: prueba ejemplo secciones cpr avnz
.PHONY=clean
CFLAGS= -g -fopenmp 

clean:
	\rm -rf prueba ejemplo secciones cpr

prueba: prueba.c
	gcc $(CFLAGS) prueba.c -o prueba

ejemplo: ejemplo.c
	gcc $(CFLAGS) ejemplo.c -o ejemplo

secciones: secciones.c
	gcc $(CFLAGS) secciones.c -o secciones

cpr: circular_primos.c
	gcc $(CFLAGS) circular_primos.c -o cpr -lm

avnz: openmp_avanzado.c
	gcc $(CFLAGS) openmp_avanzado.c -o avnz
