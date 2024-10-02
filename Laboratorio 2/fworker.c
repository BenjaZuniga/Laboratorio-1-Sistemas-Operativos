#include "fworker.h"

BMPImage *saturar(BMPImage *image, float saturacion){
    BMPImage *newImage = (BMPImage*) malloc(sizeof(BMPImage));
    newImage->header = image->header;
    newImage->infoHeader = image->infoHeader;
    newImage->width = image->width;
    newImage->height = image->height;
    newImage->pixels = (RGBPixel**) malloc(sizeof(RGBPixel*) * newImage->height);

    for(int i = 0; i < newImage->height; i++){
        newImage->pixels[i] = (RGBPixel*) malloc(sizeof(RGBPixel) * newImage->width);
    }

    for(int i = 0; i < newImage->height; i++){
        for(int j = 0; j < newImage->width; j++){
            if((image->pixels[i][j].r * saturacion) > 255) newImage->pixels[i][j].r = 255;
            else newImage->pixels[i][j].r = image->pixels[i][j].r * saturacion;
            
            if((image->pixels[i][j].g * saturacion) > 255) newImage->pixels[i][j].g = 255;
            else newImage->pixels[i][j].g = image->pixels[i][j].g * saturacion;

            if((image->pixels[i][j].b * saturacion) > 255) newImage->pixels[i][j].b = 255;
            else newImage->pixels[i][j].b = image->pixels[i][j].b * saturacion;
        }
    }

    return newImage;
}

BMPImage *escalaGrises(BMPImage *image){
    BMPImage *newImage = (BMPImage*) malloc(sizeof(BMPImage));
    newImage->header = image->header;
    newImage->infoHeader = image->infoHeader;
    newImage->width = image->width;
    newImage->height = image->height;
    newImage->pixels = (RGBPixel**) malloc(sizeof(RGBPixel*) * newImage->height);

    for(int i = 0; i < newImage->height; i++){
        newImage->pixels[i] = (RGBPixel*) malloc(sizeof(RGBPixel) * newImage->width);
    }

    for(int i = 0; i < newImage->height; i++){
        for(int j = 0; j < newImage->width; j++){
            newImage->pixels[i][j].r = (unsigned char) (image->pixels[i][j].r * 0.3) + (unsigned char) (image->pixels[i][j].g * 0.59) + (unsigned char) (image->pixels[i][j].b * 0.11);
            newImage->pixels[i][j].g = (unsigned char) (image->pixels[i][j].r * 0.3) + (unsigned char) (image->pixels[i][j].g * 0.59) + (unsigned char) (image->pixels[i][j].b * 0.11);
            newImage->pixels[i][j].b = (unsigned char) (image->pixels[i][j].r * 0.3) + (unsigned char) (image->pixels[i][j].g * 0.59) + (unsigned char) (image->pixels[i][j].b * 0.11);
        }
    }

    return newImage;
}

BMPImage *binarizar(BMPImage *image, float umbral){
    BMPImage *newImage = (BMPImage*) malloc(sizeof(BMPImage));
    newImage->header = image->header;
    newImage->infoHeader = image->infoHeader;
    newImage->width = image->width;
    newImage->height = image->height;
    newImage->pixels = (RGBPixel**) malloc(sizeof(RGBPixel*) * newImage->height);
	int newUmbral = umbral * 255;

    for(int i = 0; i < newImage->height; i++){
        newImage->pixels[i] = (RGBPixel*) malloc(sizeof(RGBPixel) * newImage->width);
    }

    for(int i = 0; i < newImage->height; i++){
        for(int j = 0; j < newImage->width; j++){
            if(image->pixels[i][j].r > newUmbral && image->pixels[i][j].g > newUmbral && image->pixels[i][j].b > newUmbral){
                newImage->pixels[i][j].r = 255;
                newImage->pixels[i][j].g = 255;
                newImage->pixels[i][j].b = 255;
            }else{
                newImage->pixels[i][j].r = 0;
                newImage->pixels[i][j].g = 0;
                newImage->pixels[i][j].b = 0;
            }
        }
    }

    return newImage;
}

