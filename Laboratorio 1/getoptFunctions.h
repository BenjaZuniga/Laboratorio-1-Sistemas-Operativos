#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#pragma once

void parse_args(int argc, char **argv, int *f, float *p, float *u, float *v, char **N, char **C, char **R); // Función que parsea los argumentos de la línea de comandos
bool isInteger(char *str);  // Función que verifica si un string es un número entero
bool isFloat(char *str);    // Función que verifica si un string es un número flotante
bool contains_flag(int argc, char **argv, char *flag); // Función que verifica si un flag está en los argumentos de la línea de comandos
void validArgs(int argc, char **argv, int f); // Función que verifica si los argumentos de la línea de comandos son válidos 