#include "getoptFunctions.h"
/*
    * parse_args: Función que parsea los argumentos de la línea de comandos
    * Entradas:
    *  - argc: Número de argumentos de la línea de comandos
    *  - argv: Arreglo de strings que representan los argumentos de la línea de comandos
    *  - f: un puntero a un entero que se usará para guardar el valor de la bandera -f (Cantidad de filtros a aplicar)
    *  - p: un puntero a un float que se usará para guardar el valor de la bandera -p (Factor de saturación)
    *  - u: un puntero a un float que se usará para guardar el valor de la bandera -u (Umbral de binarización)
    *  - v: un puntero a un float que se usará para guardar el valor de la bandera -v (Umbral de clasificación)
    *  - N: un puntero a un string que se usará para guardar el valor de la bandera -N (Nombre del prefijo de las N imagenes)
    *  - C: un puntero a un string que se usará para guardar el valor de la bandera -C (Nombre de la carpeta de las imagenes resultantes)
    *  - R: un puntero a un string que se usará para guardar el valor de la bandera -R (Nombre del archivo csv)
    *  - W: un puntero a un entero que se usará para guardar el valor de la bandera -W (Cantidad de procesos a ejecutar)
    * Salidas: la función no retorna nada, pero modifica los valores de las variables f, p, u, v, N, C, R y W
    * Descripción: la función parse_args se encarga de parsear los argumentos de la línea de comandos y modificar los valores de las variables f, p, u, v, N, C, R y W
    *       En caso de que los argumentos no sean válidos, la función imprime un mensaje de error y termina la ejecución del programa.
    *       En caso de que los argumentos sean válidos, la función modifica los valores de las variables f, p, u, v, N, C, R y W
*/

void parse_args(int argc, char **argv, int *f, float *p, float *u, float *v, char **N, char **C, char **R, int *W){
    int opt, inputNumber;
    char prefix1[] = "img";
    char prefix2[] = "imagen";
    char prefix3[] = "photo";

    while((opt = getopt(argc, argv, "N:f:p:u:v:C:R:W:")) != -1){
        switch(opt){
            case 'N':
                if(*optarg == '\0' || optarg[0] == '-'){
                    printf("Error: -N requiere un argumento\n");
                    exit(1);
                } else {
                    *N = optarg;
                    break;
                }
            case 'f':
                if(optarg == NULL || optarg[0] == '-' && !isFloat(&optarg[1])){
                    optind--;
                    break;
                } 
                if(isInteger(optarg) && atoi(optarg) > 0 && atoi(optarg) < 4){
                    *f = atoi(optarg);
                    break;
                } 
                else {
                    printf("Error: -f requiere un número entero entre 1 y 3\n");
                    exit(1);
                }
            case 'p':
                if(optarg == NULL || optarg[0] == '-' && !isFloat(&optarg[1])){
                    optind--;
                    break;
                } 
                if(isFloat(optarg) && (atof(optarg) > 0)){
                    *p = atof(optarg);
                    break;
                }
                else {
                    printf("Error: -p requiere un número positivo\n");
                    exit(1);
                }
            case 'u':
                if(optarg == NULL || optarg[0] == '-' && !isFloat(&optarg[1])){
                    optind--;
                    break;
                }
                if(isFloat(optarg) && (atof(optarg) > 0)){
                    *u = atof(optarg);
                    break;
                }
                else {
                    printf("Error: -u requiere un número positivo\n");
                    exit(1);
                }
            case 'v':
                if(optarg == NULL || (optarg[0] == '-' && !isFloat(&optarg[1]))){
                    optind--;
                    break;
                } 
                if(isFloat(optarg)  && (atof(optarg) > 0)){
                    *v = atof(optarg);
                    break;
                }
                else {
                    printf("Error: -v requiere un número positivo\n");
                    exit(1);
                }
            case 'C':
                if(*optarg == '\0' || optarg[0] == '-'){
                    printf("Error: -C requiere un argumento\n");
                    exit(1);
                } else {
                    *C = optarg;
                    break;
                }
            case 'R':
                if(*optarg == '\0' || optarg[0] == '-'){
                    printf("Error: -R requiere un argumento\n");
                    exit(1);
                } else {
                    *R = optarg;
                    break;
                }
            case 'W':
                if(optarg == NULL || optarg[0] == '-' && !isInteger(&optarg[1])){
                    optind--;
                    break;
                } 
                if(isInteger(optarg) && atoi(optarg) > 0){
                    *W = atoi(optarg);
                    break;
                }
                else {
                    printf("Error: -W requiere un número entero positivo\n");
                    exit(1);
                }
            
        }
    }

    validArgs(argc, argv, *f);

    if(*N == NULL){
        printf("Error: la bandera -N debe recibir un valor\n");
        exit(1);
    }
    if(*C == NULL){
        printf("Error: la bandera -C debe recibir un valor\n");
        exit(1);
    }
    if(*R == NULL){
        printf("Error: la bandera -R debe recibir un valor\n");
        exit(1);
    }

     // Verificar que el prefijo de las imágenes sea 'img', 'imagen' o 'photo'
    if(strcmp(*N, prefix1) != 0 && strcmp(*N, prefix2) != 0 && strcmp(*N, prefix3) != 0){
        printf("Error: el prefijo de las imágenes debe ser 'img', 'imagen' o 'photo'\n");
        exit(1);
    }
}


/*
    * isInteger: Función que verifica si un string es un número entero
    * Entradas:
    *  - str: Un string que se quiere verificar si es un número entero
    * Salidas: la función retorna un booleano que es true si el string es un número entero y false en caso contrario
    * Descripción: la función isInteger se encarga de verificar si un string es un número entero
*/
bool isInteger(char *str){
    char *endptr;
    strtol(str, &endptr, 10);
    return (*endptr == '\0');
}

/*
    * isFloat: Función que verifica si un string es un número flotante
    * Entradas:
    *  - str: Un string que se quiere verificar si es un número flotante
    * Salidas: la función retorna un booleano que es true si el string es un número flotante y false en caso contrario
    * Descripción: la función isFloat se encarga de verificar si un string es un número flotante
*/
bool isFloat(char *str){
    char *endptr;
    strtof(str, &endptr);
    return (*endptr == '\0');
}

/*
    * contains_flag: Función que verifica si un flag está en los argumentos de la línea de comandos
    * Entradas:
    *  - argc: Número de argumentos de la línea de comandos
    *  - argv: Arreglo de strings que representan los argumentos de la línea de comandos
    *  - flag: Un string que representa el flag que se quiere verificar si está en los argumentos de la línea de comandos
    * Salidas: la función retorna un booleano que es true si el flag está en los argumentos de la línea de comandos y false en caso contrario
    * Descripción: la función contains_flag se encarga de verificar si un flag está en los argumentos de la línea de comandos
*/
bool contains_flag(int argc, char **argv, char *flag){
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], flag) == 0){
            return true;
        }
    }
    return false;
}

/*
    * validArgs: Función que verifica si los argumentos de la línea de comandos son válidos
    * Entradas:
    *  - argc: Número de argumentos de la línea de comandos
    *  - argv: Arreglo de strings que representan los argumentos de la línea de comandos
    *  - f: Un entero que representa el valor de la opción -f
    * Salidas: la función no retorna nada, pero en caso de que los argumentos no sean válidos, imprime un mensaje de error y termina la ejecución del programa
    * Descripción: la función validArgs se encarga de verificar si los argumentos de la línea de comandos son válidos
*/
void validArgs(int argc, char **argv, int f){
    if(!contains_flag(argc, argv, "-f")){
        printf("Error: el programa requiere la bandera -f\n");
        exit(1);
    }

    if(!contains_flag(argc, argv, "-p")){
        printf("Error: el programa requiere la bandera -p\n");
        exit(1);
    }

    if(f == 3){
        if(!contains_flag(argc, argv, "-u")){
        printf("Error: el programa requiere la bandera -u\n");
        exit(1);
        }
    }

    if(!contains_flag(argc, argv, "-v")){
        printf("Error: el programa requiere la bandera -v\n");
        exit(1);
    }
    
    if(!contains_flag(argc, argv, "-N")){
        printf("Error: el programa requiere la bandera -N\n");
        exit(1);
    }

    if(!contains_flag(argc, argv, "-C")){
        printf("Error: el programa requiere la bandera -C\n");
        exit(1);
    }

    if(!contains_flag(argc, argv, "-R")){
        printf("Error: el programa requiere la bandera -R\n");
        exit(1);
    }
    if(!contains_flag(argc, argv, "-W")){
        printf("Error: el programa requiere la bandera -W\n");
        exit(1);
    }
}