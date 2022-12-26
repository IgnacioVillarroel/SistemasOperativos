#include "hijo.h"

void escrituraArchivoHijo(char*nombreArchivo, int anio, char * nombreJuegoMasCaro,float porcentaje_win,float porcentaje_mac,float porcentaje_linx){
	FILE * archivo = fopen(nombreArchivo,"a");
	fprintf(archivo,"ANIO: %d \n",anio);
	fprintf(archivo,"Juego mas caro: %s \n",nombreJuegoMasCaro);
	fprintf(archivo,"Windows: %f Mac: %f Linux: %f \n",porcentaje_win,porcentaje_mac,porcentaje_linx);
	fclose(archivo);
}



/*
Entrada: nombre del archivo, posicion inicial, posicion final
Salida: cantidad de lineas de un anio en el archivo  
Descripción: funcion que cuenta las lineas que son del mismo anio en un archivo
*/
int contarLineasPorAnio(char * nombreArchivo,int posicionInicio, int posicionFinal){
	FILE * archivo = fopen(nombreArchivo,"r");
	int count=0;
	int linea;
	fseek(archivo,posicionInicio,SEEK_SET);
	if(archivo == NULL){
		printf("Error: el archivo de entrada no existe.");
	}else{
		int posicion;
		while((linea = fgetc(archivo)) != EOF){
        posicion=ftell(archivo);

		if( linea == '\n'){
			
            count++;

		}
		if(posicion==posicionFinal){
			break;
		}
    
		}
	}
	return count;
	
	fclose(archivo);	
		
}
/*
Entrada: posicion de inicio, posicion de fin, nombrearchivos
Salida: arreglo de los juegos de cada anio 
Descripción: funcion que realiza la lectura del archivo intermedio por partes de los hijos utilizando fseek
*/

juego* lecturaHijo(int posicionInicio,int posicionFinal, char * nombreArchivo){
    
    FILE * archivo = fopen(nombreArchivo, "r");
	fseek(archivo,posicionInicio,SEEK_SET);
	int contador=0;
    char buffer[100000];
	char * puntero_string;
	if(archivo == NULL){
		printf("Error: el archivo de entrada no existe.");
	}
	// contamos cuantos juegos debemos almacenar
	int numJuegosTotalAnio=contarLineasPorAnio(nombreArchivo,posicionInicio,posicionFinal);
	// declaramos el arreglo de juegos
	juego * listadoJuegos =(juego *)malloc(sizeof(juego)*(numJuegosTotalAnio));
	while(contador<numJuegosTotalAnio){
		fgets(buffer,sizeof(buffer),archivo);
		puntero_string = strtok(buffer,",");
		listadoJuegos[contador].id = atoi(puntero_string);
		puntero_string = strtok(NULL,",");
		strcpy(listadoJuegos[contador].nombre,puntero_string);
		puntero_string = strtok(NULL,",");
		listadoJuegos[contador].restriccion= atoi(puntero_string);
		puntero_string = strtok(NULL,",");
		listadoJuegos[contador].precio = atof(puntero_string);
		puntero_string = strtok(NULL,",");
		strcpy(listadoJuegos[contador].proximamente,puntero_string);
		puntero_string = strtok(NULL,",");
		listadoJuegos[contador].fechaLanzamiento = atoi(puntero_string);
		puntero_string = strtok(NULL,",");
		strcpy(listadoJuegos[contador].gratuidad, puntero_string);
		puntero_string = strtok(NULL,",");
		strcpy(listadoJuegos[contador].windows,puntero_string);
		puntero_string = strtok(NULL,",");
		strcpy(listadoJuegos[contador].mac,puntero_string);
		puntero_string = strtok(NULL,",");
		strcpy(listadoJuegos[contador].linuxx,puntero_string);
		contador++;
	}
	return listadoJuegos;
}

/*
Entrada: lista de juegos por anio, tamaño de la lista
Salida: id del juego mas caro
Descripción:funcion que calcula el juego mas caro 
*/
int  calcularJuegoMasCaro(juego*listadoJuegosAnio, int n){
	float maxPrecio=listadoJuegosAnio[0].precio;
	float maxTemporal;
	int posicionJuegoMasCaro;
	for(int i=0;i<n;i++){
		maxTemporal=listadoJuegosAnio[i].precio;
		if(maxTemporal>maxPrecio){
			maxTemporal=listadoJuegosAnio[i].precio;
			posicionJuegoMasCaro=i;
		}
	}

	return posicionJuegoMasCaro;
} 

/*
Entrada: lista de juegos por anio, tamaño de la lista
Salida: la cantidad de juego gratis
Descripción: funcion que cuenta cuantos juegos gratis existen
*/
int contadorJuegosGratis(juego * listadoJuegosAnio, int n){
    int cantidadJuegosGratis=0;
    for(int i=0;i<n;i++){
        if(strcmp(listadoJuegosAnio[i].gratuidad,"True")){
            cantidadJuegosGratis++;
        }
    }
    return cantidadJuegosGratis;
}
/*
Entrada: lista de juegos por anio, tamaño de la lista
Salida:
Descripción: funcion que obtiene los juegos gratis de la lista de juegos por anio



int * obtenerJuegosGratis(int*listadoJuegosAnio, int n){
	int m=contadorJuegosGratis(listadoJuegosAnio,n);
    int * listadoJuegosGratis=malloc(sizeof(juego)*(m));
	for(int i=0;i<m;i++){
		 if(strcmp(listadoJuegosAnio[i].gratuidad,"True")){
            listadoJuegosGratis[i] =;
        }
	}

	return listadoJuegosGratis;
}*/


 /*
Entrada: lista de juegos por anio, tamaño de la lista
Salida:
Descripción: funcion que obtiene el promedio de los precios de la lista de juegos por anio
*/   

float  calcularPromedioAnio(juego*listadoJuegosAnio, int n){
	float sumaPrecios=0;
	
	for(int i=0;i<n;i++){
		sumaPrecios=listadoJuegosAnio[i].precio+sumaPrecios;
	}
    
	return (sumaPrecios/n);
} 


/*
Entrada: lista de juegos por anio, tamaño de la lista
Salida: lista de los porcentajes de juegos por plataforma;
Descripción: funcion que obtiene los porcentajes de las plataformas de la lista de juegos por anio
*/   
float * calcularPorcentajePlataforma(juego*listadoJuegosAnio, int n){
    float * porcentajesPlataforma=malloc(sizeof(float)*(3));
    float cantidadLin=0;
    float cantidadWin=0;
    float cantidadMac=0;
	for(int i=0;i<n;i++){
		if(strcmp(listadoJuegosAnio[i].windows,"Yes")){
            cantidadWin++;
        }
        if(strcmp(listadoJuegosAnio[i].linuxx,"Yes")){
            cantidadLin++;
        }
        if(strcmp(listadoJuegosAnio[i].mac,"Yes")){
            cantidadMac++;
        }
	}
	printf("cantidadWin: %f",cantidadWin);
    float total=cantidadWin+cantidadLin+cantidadMac;
	printf("total=%f \n\n",total);
    float porcentajeWin=(100 * cantidadLin)/total;
    float porcentajeLin=(100 * cantidadMac)/total;
    float porcentajeMac=(100 * cantidadWin)/total;
    porcentajesPlataforma[0]=porcentajeWin;
    porcentajesPlataforma[1]=porcentajeLin;
    porcentajesPlataforma[2]=porcentajeMac;
    
    
	return porcentajesPlataforma;
}
/*
Entrada: lista de juegos por anio, tamaño de la lista
Salida: id del juego del menor precio
Descripción: funcion que obtiene el juego de menor precio de la lista de juegos por anio
*/
   
juego menorPrecio (juego*listadoJuegosAnio, int n){
    float minPrecio = listadoJuegosAnio[0].precio;
    float auxiliarMinimo;
    juego juegoMasBarato;
    for (int i = 0; i < n; i++)
    {
        auxiliarMinimo=listadoJuegosAnio[i].precio;
        if(auxiliarMinimo<minPrecio){
            auxiliarMinimo=listadoJuegosAnio[i].precio;
            juegoMasBarato=listadoJuegosAnio[i];
        }
    }
    return juegoMasBarato;
    

}


