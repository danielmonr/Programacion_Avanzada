ALL: prueba ejemplo
.PHONY=clean

clean:
	\rm -rf prueba ejemplo

prueba: prueba.c
	gcc -fopenmp prueba.c -o prueba

ejemplo: ejemplo.c
	gcc -fopenmp ejemplo.c -o ejemplo

