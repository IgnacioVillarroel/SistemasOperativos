#include "padre.h"


/*
Entrada: lista de struct anioPosicion, posicion final, anio, tamaño de la lista
Salida: lista de struct anioPosicion con un dato agregado
Descripción: funcion que agrega datos de una lista tipo struct anio Posicion
*/
anioPosicion * agregarDatosAnioPosicion(anioPosicion* lista,int posicionFinal,int anio,int *n){
    anioPosicion * nuevalista = malloc(sizeof(anioPosicion)*(*n+1));

    for(int i=0;i<*n;i++){
        nuevalista[i].anio = lista[i].anio;
		nuevalista[i].posicionFinal = lista[i].posicionFinal;
    }

    nuevalista[*n].posicionFinal = posicionFinal;
	nuevalista[*n].anio = anio;
	*n=*n+1;
    free(lista);
    return nuevalista; 
} 	


/*
Entrada: lista de tipo int, dato para agregar, tamaño lista
Salida: lista actualizada
Descripción: funcion que agrega datos a una lista tipo entero
*/
int * agregarDatos(int* lista,int p,int *n){
    int * nuevalista = malloc(sizeof(int)*(*n+1));

    for(int i=0;i<*n;i++){
        nuevalista[i] = lista[i];
    }

    nuevalista[*n] = p;
	*n=*n+1;
    free(lista);
    return nuevalista; 
} 	

/*
Entrada: nombre del archivo
Salida: cantidad de lineas
Descripción: funcion que cuenta las lineas de un archivo
*/
int contarLineas(char * nombreArchivo){
	FILE * archivo = fopen(nombreArchivo,"r");
	int count=0;
	int linea;
	if(archivo == NULL){
		printf("Error: el archivo de entrada no existe.");
	}else{
		while((linea = fgetc(archivo)) != EOF){
        if( linea == '\n')
            count++;
		}
	}
    
	fclose(archivo);
	return count;
}



/*
Entrada: nombre del archivo, cantidad de  juegos, cantidad de anios
Salida: lista de struct anioPosicion con los datos de los anios y sus posiciones
Descripción: funcion que escribe el archivo intermedio 
*/
anioPosicion * escribirListadoJuego(char* nombreArchivo, juego* listadoJuegos, int numJuegosTotal, int* numeroAnios){
    FILE* archivo = fopen(nombreArchivo, "w");
	anioPosicion * posicionesFinales= malloc(sizeof(anioPosicion)*(*numeroAnios));
	int fechaLanzamientoAux=listadoJuegos[0].fechaLanzamiento;
	long posicionFinal;

    if(archivo == NULL){
		
        printf("No se pudo abrir el archivo");

    }
	
	printf("\n Procesos hijos y las que seran sus posiciones finales en el archivo intermedio \n");
    for(int contador = 0; contador < numJuegosTotal; contador++){
		// Si el anio es diferente al anterior, se agrega a la lista de posiciones finales dado que esa es su posicion final
		if(listadoJuegos[contador].fechaLanzamiento!=fechaLanzamientoAux){
			// printeamos por pantalla para que se verifique que se realizo esto de forma correcta
			printf("%ld posicion de la ultima linea del anio %d\n",posicionFinal,fechaLanzamientoAux);
			posicionesFinales=agregarDatosAnioPosicion(posicionesFinales,posicionFinal,fechaLanzamientoAux,&(*numeroAnios));
			fechaLanzamientoAux=listadoJuegos[contador].fechaLanzamiento;
		}
		fprintf(archivo, "%d,%s,%d,%f,%s,%d,%s,%s,%s,%s", listadoJuegos[contador].id, listadoJuegos[contador].nombre, listadoJuegos[contador].restriccion, listadoJuegos[contador].precio, listadoJuegos[contador].proximamente, listadoJuegos[contador].fechaLanzamiento, listadoJuegos[contador].gratuidad, listadoJuegos[contador].windows, listadoJuegos[contador].mac, listadoJuegos[contador].linuxx);
		posicionFinal=ftell(archivo);
		
    }
	fclose(archivo);
	return posicionesFinales;
}

/*
Entrada: listado de juegos, inicio, medio, fin
Salida: -
Descripción: funcion que ordena el listado de juegos por fecha de lanzamiento
*/

void merge(juego* listadoJuegos,int inicio,int medio,int fin){
	
	juego* listaAux = (juego*)calloc(fin-inicio+1,sizeof(juego));
	int izq = inicio;
	int der = medio+1;
	int k = 0;

	
	while(izq<=medio && der<=fin){
		// Sentencia para que ordene por anio de lanzamiento
		if(listadoJuegos[izq].fechaLanzamiento<=listadoJuegos[der].fechaLanzamiento){
			
			listaAux[k] = listadoJuegos[izq];
			izq++;
		}else{
			
			listaAux[k] = listadoJuegos[der];
			der++;
		}
		k++;
	} 
	
	for(;izq<=medio;izq++){
		listaAux[k] = listadoJuegos[izq];
		k++;
	}

	for(;der<=fin;der++){
		listaAux[k] = listadoJuegos[der];
		k++;
	}

	int l=0;
	for(k=inicio;k<=fin;k++){
		listadoJuegos[k] = listaAux[l];
		l++;
	}
	free(listaAux);
	return;
}

/*
Entrada: Listado de juegos, inicio, fin
Salida: -
Descripción: mergeSort que ordenara la lista de juegos
*/
void mergeSort(juego* listadoJuegos, int inicio, int fin){

	if(inicio==fin){
		return;
	} else{ 
		int medio = (inicio+fin)/2;

		mergeSort(listadoJuegos,inicio,medio);

		mergeSort(listadoJuegos,medio+1,fin);

		merge(listadoJuegos,inicio,medio,fin);
		return;
	}
}
