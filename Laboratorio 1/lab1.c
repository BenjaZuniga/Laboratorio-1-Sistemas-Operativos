#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/stat.h>
#include "getoptFunctions.h"
#include "funciones.h"
#include "render.h"

// Consideraciones: Para que el programa funcione deben estar declaradas las banderas -N, -f, -p, -v, -C y -R y la bandera -u solo en caso de 
//                  que la bandera f sea 3 o no se le haya dado un valor
int main(int argc, char** argv){
    int opt;
    int f = 3; // Valor por defecto de la cantidad de filtros
    float p = 1.3, u = 0.5, v = 0.5; // Valores por defecto de los parametros de los filtros
    char *N = NULL, *C = NULL, *R = NULL;// Valores por defecto de los nombres de los archivos
    char *resultFolder = malloc(200); // Carpeta de resultados
    char *auxName = malloc(200); // Nombre auxiliar
    DIR *folderImages, *folder; // Carpeta de imagenes
    struct dirent *dirent; // Imagenes de la carpeta

    parse_args(argc, argv, &f, &p, &u, &v, &N, &C, &R); // Getopt de los argumentos

    strcpy(auxName, R); // Nombre del archivo de clasificación
    strcat(auxName, ".csv"); // Se le agrega ".csv" para que sea un archivo csv
    remove(auxName); // Elimina el archivo csv con los resultados si ya existe
    
    rmdir(C); // Elimina la carpeta de resultados si ya existe
    mkdir(C, 0755); // Crea la carpeta de resultados

    strcat(resultFolder, C); // Nombre de resultados
    strcat(resultFolder, "/"); // Se le agrega "/" para que sea una dirección

    folderImages = opendir("./Imagenes_Iniciales"); // Abre la carpeta actual
    folder = opendir(".");
    
    render(dirent, folderImages, f, p, u, v, N, C, R, resultFolder); // Procesa las imagenes

    return 0; // Se termina el programa
}