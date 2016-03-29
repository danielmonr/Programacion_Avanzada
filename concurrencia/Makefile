ALL: hilos filosofos barrera
.PHONY=clean

hilos:hilos.c
	gcc -g hilos.c -o hilos -pthread

filosofos:filosofos.c
	gcc -g filosofos.c -o filosofos -lpthread

barrera:barreras.c
	gcc -g barreras.c -o barrera -lpthread
clean:
	\rm -f  hilos filosofos barrera
