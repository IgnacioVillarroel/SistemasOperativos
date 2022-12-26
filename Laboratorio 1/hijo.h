#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include "estructura.h"


//Se definen las cabeceras de cada funciones correspondiente al hijo.c

int calcularJuegoMasCaro(juego* istadoJuegosAnio, int n);
int contadorJuegosGratis(juego* listadoJuegosAnio, int n);
float  calcularPromedioAnio(juego*listadoJuegosAnio, int n);
int calcularJuegoMasBarato(juego* listadoJuegosAnio, int n);
juego* lecturaHijo(int posicionInicio,int posicionFinal, char * nombreArchivo);
float * calcularPorcentajePlataforma(juego*listadoJuegosAnio, int n);
void imprimirJuego(juego* listadoJuegosAnio, int n);
void imprimirJuegoMasCaro(juego* listadoJuegosAnio, int n);
void imprimirJuegosGratis(juego* listadoJuegosAnio, int n);
void imprimirPromedioAnio(juego* listadoJuegosAnio, int n);
void imprimirJuegoMasBarato(juego* listadoJuegosAnio, int n);
void escrituraArchivoHijo(char*nombreArchivo, int anio, char * nombreJuegoMasCaro,float porcentaje_win,float porcentaje_mac,float porcentaje_linx);
