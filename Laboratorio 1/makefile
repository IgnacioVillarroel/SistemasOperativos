#Archivo makefile para compilación de los archivos.
#lm para ejecución de funciones matemáticas, como pow.
lab1: lab1.o funciones.o vis.o
	gcc -o lab1 lab1.c funciones.o -Wall -lm
	gcc -o vis vis.c funciones.o -Wall -lm

lab1.o: lab1.c
	gcc -c lab1.c -Wall

funciones.o: funciones.c
	gcc -c funciones.c -Wall

vis.o: vis.c
	gcc -c vis.c -Wall

.PHONY: clean