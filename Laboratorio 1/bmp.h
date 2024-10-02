#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma once

// Estructura que representa el header de un archivo BMP
// Contiene los campos type, size, reserved1, reserved2 y offset
typedef struct BMPHeader{
    uint16_t type;          // 2 bytes que representan el tipo de archivo BMP (0x4D42)
    uint32_t size;          // 4 bytes que representan el tamaño del archivo BMP en bytes
    uint16_t reserved1;     // 2 bytes reservados 
    uint16_t reserved2;     // 2 bytes reservados
    uint32_t offset;        // 4 bytes que representan el offset en bytes desde el inicio del archivo hasta los datos de la imagen
} BMPHeader;


// Estructura que representa el info header de un archivo BMP
// Contiene los campos size, width, height, planes, bits, compression, imageSize, xResolution, yResolution, colors e importantColors
typedef struct BMPInfoHeader{
    uint32_t size;              // 4 bytes que representan el tamaño del info header en bytes
    uint32_t width;             // 4 bytes que representan el ancho de la imagen en pixeles
    uint32_t height;            // 4 bytes que representan el alto de la imagen en pixeles
    uint16_t planes;            // 2 bytes que representan el número de planos de color
    uint16_t bits;              // 2 bytes que representan el número de bits por pixel
    uint32_t compression;       // 4 bytes que representan el tipo de compresión
    uint32_t imageSize;         // 4 bytes que representan el tamaño de la imagen en bytes
    uint32_t xResolution;       // 4 bytes que representan la resolución horizontal en pixeles por metro
    uint32_t yResolution;       // 4 bytes que representan la resolución vertical en pixeles por metro
    uint32_t colors;            // 4 bytes que representan el número de colores en la paleta
    uint32_t importantColors;   // 4 bytes que representan el número de colores importantes
} BMPInfoHeader;

// Estructura que representa un pixel RGB
// Contiene los campos r, g y b que representan los valores de los canales rojo, verde y azul respectivamente
typedef struct RGBPixel{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGBPixel;

// Estructura que representa una imagen BMP
// Contiene los campos width y height que representan el ancho y alto de la imagen en pixeles respectivamente
typedef struct BMPImage{
    int width;              // Ancho de la imagen en pixeles
    int height;             // Alto de la imagen en pixeles
    RGBPixel *pixelArray;   // Arreglo de pixeles que representan la imagen
} BMPImage;


BMPImage *readBMP(char *filename);              // Función que lee un archivo BMP y retorna una estructura BMPImage
void freeBMP(BMPImage *image);                  // Función que libera la memoria de una estructura BMPImage
void writeBMP(char *filename, BMPImage *image); // Función que escribe una estructura BMPImage en un archivo BMP

