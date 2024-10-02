#include <stdio.h>

#pragma pack(push, 1)
#include "bmp.h"

BMPImage *readBMP(char *filename){
    FILE *file = fopen(filename, "rb");
    if(!file){
        fprintf(stderr, "Error al abrir el archivo %s\n", filename);
        return NULL;
    }

    BMPHeader header;
    fread(&header, sizeof(BMPHeader), 1, file);
    if(header.type != 0x4D42){
        fprintf(stderr, "El archivo %s no es un BMP\n", filename);
        fclose(file);
        return NULL;
    }

    BMPInfoHeader infoHeader;
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    BMPImage *image = (BMPImage*) malloc(sizeof(BMPImage));
    image->width = infoHeader.width;
    image->height = infoHeader.height;
    image->pixels = (RGBPixel**) malloc(sizeof(RGBPixel*) * image->height);
    for(int i = 0; i < image->height; i++){
        image->pixels[i] = (RGBPixel*) malloc(sizeof(RGBPixel) * image->width);
    }

    fseek(file, header.offset, SEEK_SET);
    for(int i = image->height - 1; i >= 0; i--){
        for(int j = 0; j < image->width; j++){
            fread(&image->pixels[i][j], sizeof(RGBPixel), 1, file);
        }
    }

    image->header = header;
    image->infoHeader = infoHeader;

    fclose(file);
    return image;
}

void freeBMP(BMPImage *image){
    if(image){
        for(int i = 0; i < image->height; i++){
            free(image->pixels[i]);
        }
        free(image->pixels);
        free(image);
    }
}

void writeBMP(char *filename, BMPImage *image){
    FILE *file = fopen(filename, "wb");
    if(!file){
        fprintf(stderr, "Error al abrir el archivo %s\n", filename);
        return;
    }

    fwrite(&image->header, sizeof(BMPHeader), 1, file);
    fwrite(&image->infoHeader, sizeof(BMPInfoHeader), 1, file);

    fseek(file, image->header.offset, SEEK_SET);
    for(int i = image->height - 1; i >= 0; i--){
        for(int j = 0; j < image->width; j++){
            fwrite(&image->pixels[i][j], sizeof(RGBPixel), 1, file);
        }
    }

    fclose(file);
    return;
}