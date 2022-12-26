#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include "estructura.h"

int contarLineas(char * nombreArchivo);
int * agregarDatos(int* lista,int p,int *n);
anioPosicion * agregarDatosAnioPosicion(anioPosicion* lista,int posicionFinal,int anio,int *n);
int contarLineasPorAnio(char * nombreArchivo,int posicionInicio, int posicionFinal);
anioPosicion * escribirListadoJuego(char* nombreArchivo, juego* listadoJuegos, int numJuegosTotal, int* numeroAnios);
void merge(juego* listadoJuegos,int inicio,int medio,int fin);
void mergeSort(juego* listadoJuegos,int inicio,int fin);
void imprimirListadoJuego(juego* listadoJuegos, int numJuegosTotal);

