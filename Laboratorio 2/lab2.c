#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	extern char *optarg; //Almacena los argumentos introducidos después de haber indicado la variable.
    extern int optind; // Almacena el número de argumentos introducidos.
    int option;
    int iflag = 0;
    int oflag = 0;
    int error = 0;
    // Variables de entrada
	char anio[100] = "0";
	char precioMenor[100] = "0";
    char nombre_archivo_salida[100];
    char nombre_archivo_entrada[100];
    char procesoPorPantalla[100] = "0";
    char cantidadWorkers[100] = "1";
    while((option = getopt(argc, argv, "i:o:d:p:n:b")) != -1){
        switch(option){
            case 'i':
                iflag = 1;
                strcpy(nombre_archivo_entrada,optarg);
                break;
            case 'o':
                oflag = 1;
                strcpy(nombre_archivo_salida,optarg);
                break;
            case 'd':
                strcpy(anio,optarg);
                break;
            case 'p':
                strcpy(precioMenor,optarg);
                break;
            case 'n':
                strcpy(cantidadWorkers,optarg);
                break;
            case 'b':
                strcpy(procesoPorPantalla,"1");
                break;
            case '?':
                error = 1;
                break;
            exit(0);
        }
    }
    // Verificaciones de archivo de entradas
    if(iflag!=1){
        printf("Por favor ingresar nombre del archivo de entrada!!\n");
        return 0;
    }
    // Verificacion de archivo de salida
    if(oflag!=1){
        printf("Por favor ingresar nombre del archivo de salida!!\n");
        return 0;
    }
    // Verificacion de error
    if(error==1){
        printf("Por favor ingrese las variables de entrada!!\n");
        return 0;
    }
    // verificacion cantidad de workers
    if(atoi(cantidadWorkers)<1){
        printf("Por favor ingresar un numero de workers mayor a 0\n");
        return 0;
    }
    // Verificaciones del anio incial
    if(atoi(anio)<0){
        printf("Por favor ingresar un numero de año mayor o igual a 0\n");
        return 0;
    }
    // Verificaciones del precio menor.
    if(atof(precioMenor)<0){
        printf("Por favor ingresar un numero de precio mayor o igual a 0\n");
        return 0;
    }
    // Se ejecuta el broker
    int pid= fork();
    if(pid==0){
        execlp("./broker", "broker", nombre_archivo_entrada,nombre_archivo_salida, anio, precioMenor, cantidadWorkers,procesoPorPantalla,NULL);
    }
        
    return 0;
}
