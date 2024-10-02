#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include "getoptFunctions.h"
#include "funciones.h"

void render(struct dirent *directory,DIR *folder, int f, float p,float u, float v, char *N, char *C, char *R, char *resultFolder); // Funcion de procesamiento de imagenes