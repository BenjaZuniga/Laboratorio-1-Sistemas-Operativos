#include <stdio.h>


#pragma pack(push, 1)
#include "bmp.h"

// Entradas: la función saturar recibe:
//          - filename: Un string que representa el nombre del archivo BMP que se quiere leer.
// Salidas: la función retorna un puntero a una estructura BMPImage que representa una imagen BMP.
// Descripción: la función readBMP se encarga de leer un archivo BMP y retornar una estructura BMPImage que representa la imagen.
BMPImage *readBMP(char* filename){
    FILE *file = fopen(filename, "rb");
    if(!file){
        fprintf(stderr, "Error: no se pudo abrir el archivo\n");
        return NULL;
    }

    BMPHeader header;
    fread(&header, sizeof(BMPHeader), 1, file);
    if(header.type != 0x4D42){  //0x4D42 = "BM"
        fprintf(stderr, "Error: archivo no es un BMP\n");
        fclose(file);
        return NULL;
    }

    BMPInfoHeader infoHeader;
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    BMPImage* image = (BMPImage*)malloc(sizeof(BMPImage));
    image->width = infoHeader.width;
    image->height = infoHeader.height;
    image->pixelArray = (RGBPixel*)malloc(sizeof(RGBPixel) * image->width * image->height);

    fseek(file, header.offset, SEEK_SET);
    int padding = (4 - (image->width * sizeof(RGBPixel)) % 4) % 4;
    for(int y = infoHeader.height - 1; y >= 0; y--){
        for(int x = 0; x < infoHeader.width; x++){
            RGBPixel pixel;
            fread(&pixel, sizeof(RGBPixel), 1, file);
            image->pixelArray[y * infoHeader.width + x] = pixel;
        }
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return image;
}

// Entradas: la función freeBMP recibe:
//          - image: Un puntero a una estructura BMPImage que representa una imagen BMP.
// Salidas: la función no retorna nada.
// Descripción: la función freeBMP se encarga de liberar la memoria de una estructura BMPImage.
void freeBMP(BMPImage *image){
    if(image){
        free(image->pixelArray);
        free(image);
    }
}

// Entradas: la función writeBMP recibe:
//          - filename: Un string que representa el nombre del archivo BMP que se quiere escribir.
//          - image: Un puntero a una estructura BMPImage que representa una imagen BMP.
// Salidas: la función no retorna nada.
// Descripción: la función writeBMP se encarga de escribir una estructura BMPImage en un archivo BMP con un nombre dado.
void writeBMP(char* filename, BMPImage* image){
    FILE *file = fopen(filename, "wb");
    if(!file){
        fprintf(stderr, "Error: no se pudo crear el archivo\n");
        return;
    }

    BMPHeader header;
    header.type = 0x4D42;
    header.size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + image->width * image->height * sizeof(RGBPixel);
    header.offset = sizeof(BMPHeader) + sizeof(BMPInfoHeader);

    BMPInfoHeader infoHeader;
    infoHeader.size = sizeof(BMPInfoHeader);
    infoHeader.width = image->width;
    infoHeader.height = image->height;
    infoHeader.planes = 1;
    infoHeader.bits = 24;
    infoHeader.imageSize = image->width * image->height * sizeof(RGBPixel);

    fwrite(&header, sizeof(BMPHeader), 1, file);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    int padding = (4 - (image->width * sizeof(RGBPixel)) % 4) % 4;
    for(int y = image->height -1; y >= 0; y--){
        for(int x = 0; x < image->width; x++){
            RGBPixel pixel = image->pixelArray[y * image->width + x];
            fwrite(&pixel, sizeof(RGBPixel), 1, file);
        }

        RGBPixel paddingPixel = {0, 0, 0};
        fwrite(&paddingPixel, sizeof(RGBPixel), padding, file);
    }

    fclose(file);
}

