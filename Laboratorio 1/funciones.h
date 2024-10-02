#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bmp.h"
#pragma once

BMPImage *saturar(BMPImage *image, float saturacion);   // Función que satura una imagen BMP
BMPImage *escalaGrises(BMPImage *image);                // Función que convierte una imagen BMP a escala de grises
BMPImage *binarizar(BMPImage *image, int umbral);       // Función que binariza una imagen BMP
int nearlyBlack(BMPImage *image, float umbral);         // Función que verifica si una imagen BMP es "nearly black"