ALL: hilos filosofos
.PHONY=clean

hilos:hilos.c
	gcc -g hilos.c -o hilos -pthread

filosofos:filosofos.c
	gcc -g filosofos.c -o filosofos -lpthread
clean:
	\rm -f  hilos filosofos
