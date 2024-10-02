#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma once

// Estructura que representa el Header de un BMP

typedef struct BMPHeader{
    uint16_t type;       // "BM", primeros 2 bytes que representan el tipo de archivo BMP 
    uint32_t size;      // Tamaño del archivo en bytes, 4 bytes
    uint16_t reserved1; // Reservado, 2 bytes, no relevante para el proyecto
    uint16_t reserved2; // Reservado, 2 bytes, no relevante para el proyecto
    uint32_t offset;    // Offset de la imagen, 4 bytes
} BMPHeader;


typedef struct BMPInfoHeader{
    uint32_t size;              // Tamaño del header, 4 bytes
    uint32_t width;             // Ancho de la imagen, 4 bytes
    uint32_t height;            // Alto de la imagen, 4 bytes
    uint16_t planes;            // Planos de color, 2 bytes
    uint16_t bitsPerPixel;      // Bits por pixel, 2 bytes
    uint32_t compression;       // Compresión, 4 bytes
    uint32_t imageSize;         // Tamaño de la imagen, 4 bytes
} BMPInfoHeader;

// Estructura que representa un pixel de la imagen BMP

typedef struct RGBPixel{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGBPixel;


// Estructura que representa una imagen BMP
typedef struct BMPImage{
    int height;
    int width;
    RGBPixel **pixels;
    BMPHeader header;
    BMPInfoHeader infoHeader;
} BMPImage;

// Funciones para manejar imagenes BMP
BMPImage *readBMP(char *filename); // Lee una imagen BMP y la almacena en una estructura BMPImage
void freeBMP(BMPImage *image); // Libera la memoria de una estructura BMPImage
void writeBMP(char *filename, BMPImage *image); // Escribe una estructura BMPImage en un archivo BMP