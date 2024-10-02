#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h> 
#include <fcntl.h>
#include "bmp.h"

// Funciones para broker
BMPImage **splitImage(BMPImage *image, int W); // Función que divide una imagen BMP en W partes
BMPImage *joinImage(BMPImage **images, int W); // Función que une W imágenes BMP en una sola
int nearlyBlack(BMPImage *image, float umbral);         // Función que verifica si una imagen BMP es "nearly black"

// Funciones para worker [PLACEHOLDER]
BMPImage *saturar(BMPImage *image, float saturacion);   // Función que satura una imagen BMP
BMPImage *escalaGrises(BMPImage *image);                // Función que convierte una imagen BMP a escala de grises
BMPImage *binarizar(BMPImage *image, int umbral);       // Función que binariza una imagen BMP
