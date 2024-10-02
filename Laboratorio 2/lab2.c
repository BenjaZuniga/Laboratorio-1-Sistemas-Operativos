#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include "getoptFunctions.h"



// Consideraciones: Para que el programa funcione deben estar declaradas las banderas -N, -f, -p, -v, -C, -R y -W y la bandera -u solo en caso de 
//                  que la bandera f sea 3 o no se le haya dado un valor
//                  se asumira que W es 1 si no se le da un valor
int main(int argc, char** argv) {
    int f = 3, W = 1;
    float p = 1.3, u = 0.5, v = 0.5; // Valores por defecto de los parametros de los filtros
    char *N = NULL, *C = NULL, *R = NULL; // Valores por defecto de los nombres de los archivos

    parse_args(argc, argv, &f, &p, &u, &v, &N, &C, &R, &W); // Se parsean los argumentos de la linea de comandos

    // Guardo los valores de los parametros en strings
    char pstring[10], ustring[10], vstring[10], fstring[10], Wstring[10];
    snprintf(pstring, sizeof(pstring), "%.2f", p);
    snprintf(ustring, sizeof(ustring), "%.2f", u);
    snprintf(vstring, sizeof(vstring), "%.2f", v);
    snprintf(fstring, sizeof(fstring), "%d", f);
    snprintf(Wstring, sizeof(Wstring), "%d", W);

    // Creo el arreglo de argumentos para el broker
    char *argv2[] = {"./lab2.c", "-f", fstring, "-p", pstring, "-u", ustring, "-v", vstring, "-N", N, "-C", C, "-R", R, "-W", Wstring, NULL};
    
    int pid = fork(); // Se crea un proceso hijo
    if(pid == 0){
        execv("./broker", argv2); // Se ejecuta el broker
        perror("Error en execv");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }

    return 0;
}