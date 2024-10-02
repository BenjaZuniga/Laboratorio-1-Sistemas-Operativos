#include "funciones.h"

// Entradas: la función saturar recibe:
//          - image: Un puntero a una estructura BMPImage que representa una imagen BMP.
//          - saturacion: Un número flotante que representa la saturación que se le quiere aplicar a la imagen.
// Salidas: la función retorna un puntero a una estructura BMPImage que representa una imagen BMP con la saturación aplicada.
// Descripción: la función saturar se encarga de aplicarle una saturación a una imagen BMP.
BMPImage* saturar(BMPImage* image, float saturacion){
    BMPImage* newImage = (BMPImage*)malloc(sizeof(BMPImage));
    newImage->width = image->width;
    newImage->height = image->height;
    newImage->pixelArray = (RGBPixel*)malloc(sizeof(RGBPixel) * newImage->width * newImage->height);

    for(int y = 0; y < newImage->height; y++){
        for(int x = 0; x < newImage->width; x++){
            RGBPixel pixel = image->pixelArray[y * newImage->width + x];
            if((pixel.r * saturacion)>255){
                pixel.r = 255;
            }else{
                pixel.r = (unsigned char)(pixel.r * saturacion);
            }if((pixel.g * saturacion)>255){
                pixel.g = 255;
            }else{
                pixel.g = (unsigned char)(pixel.g * saturacion);
            }if((pixel.b * saturacion)>255){
                pixel.b = 255;
            }else{
                pixel.b = (unsigned char)(pixel.b * saturacion);
            }
            newImage->pixelArray[y * newImage->width + x] = pixel;
        }
    }

    return newImage;
}

// Entradas: la función escalaGrises recibe:
//          - image: Un puntero a una estructura BMPImage que representa una imagen BMP.
// Salidas: la función retorna un puntero a una estructura BMPImage que representa una imagen BMP en escala de grises.
// Descripción: la función escalaGrises se encarga de convertir una imagen BMP a escala de grises.
BMPImage* escalaGrises(BMPImage* image){
    BMPImage* newImage = (BMPImage*)malloc(sizeof(BMPImage));
    newImage->width = image->width;
    newImage->height = image->height;
    newImage->pixelArray = (RGBPixel*)malloc(sizeof(RGBPixel) * newImage->width * newImage->height);

    for(int y = 0; y < newImage->height; y++){
        for(int x = 0; x < newImage->width; x++){
            RGBPixel pixel = image->pixelArray[y * newImage->width + x];
            pixel.r = (unsigned char)(pixel.r * 0.3) +  (unsigned char)(pixel.g * 0.59) + (unsigned char)(pixel.b * 0.11);
            pixel.g = (unsigned char)(pixel.r * 0.3) +  (unsigned char)(pixel.g * 0.59) + (unsigned char)(pixel.b * 0.11);
            pixel.b = (unsigned char)(pixel.r * 0.3) +  (unsigned char)(pixel.g * 0.59) + (unsigned char)(pixel.b * 0.11);
            newImage->pixelArray[y * newImage->width + x] = pixel;
        }
    }

    return newImage;
}

// Entradas: la función binarizar recibe:
//          - image: Un puntero a una estructura BMPImage que representa una imagen BMP.
//          - umbral: Un número entero que representa el umbral para binarizar la imagen.
// Salidas: la función retorna un puntero a una estructura BMPImage que representa una imagen BMP binarizada.
// Descripción: la función binarizar se encarga de binarizar una imagen BMP.
BMPImage* binarizar(BMPImage* image, int umbral){
    BMPImage* newImage = (BMPImage*)malloc(sizeof(BMPImage));
    newImage->width = image->width;
    newImage->height = image->height;
    newImage->pixelArray = (RGBPixel*)malloc(sizeof(RGBPixel) * newImage->width * newImage->height);

    for(int y = 0; y < newImage->height; y++){
        for(int x = 0; x < newImage->width; x++){
            RGBPixel pixel = image->pixelArray[y * newImage->width + x];
            if(pixel.r > umbral && pixel.g > umbral && pixel.b > umbral){
                newImage->pixelArray[y * newImage->width + x].r = 255;
                newImage->pixelArray[y * newImage->width + x].g = 255;
                newImage->pixelArray[y * newImage->width + x].b = 255;
            }else{
                newImage->pixelArray[y * newImage->width + x].r = 0;
                newImage->pixelArray[y * newImage->width + x].g = 0;
                newImage->pixelArray[y * newImage->width + x].b = 0;
            }
        }
    }

    return newImage;
}

// Entradas: la función nearlyBlack recibe:
//          - image: Un puntero a una estructura BMPImage que representa una imagen BMP.
//          - umbral: Un número flotante que representa el umbral para determinar si una imagen es "nearly black".
// Salidas: la función retorna un entero que representa si la imagen es "nearly black" o no.
// Descripción: la función nearlyBlack se encarga de determinar si una imagen es "nearly black" o no basado en un umbral dado.
int nearlyBlack(BMPImage* image, float umbral){
    long counter = 0;
    float percentage = 0;
    for(int y = 0; y < image->height; y++){
        for(int x = 0; x < image->width; x++){
            RGBPixel pixel = image->pixelArray[y * image->width + x];
            if(pixel.r == 255 && pixel.g == 255 && pixel.b == 255){
                counter++;
            }
        }
    }
    float pixels = image->width*image->height;
    percentage = counter/pixels;
    //printf("Cantidad de pixeles negros: %ld\nCantidad de pixeles: %f\nPorcentaje de la imagen en negro: %f\n", counter, pixels,percentage);
    if(percentage > umbral){
        return 1;       
    }else{
        return 0;
    }
}