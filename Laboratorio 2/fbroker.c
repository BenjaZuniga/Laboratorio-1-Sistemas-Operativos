#include "fbroker.h"

BMPImage **splitImage(BMPImage *image, int W){
    BMPImage **images = (BMPImage**) malloc(sizeof(BMPImage*) * W);
    int width = image->width / W;
    int lastWidth = image->width % W + width;
    int height = image->height;

    for(int i = 0; i < W; i++){
        images[i] = (BMPImage*) malloc(sizeof(BMPImage));
        images[i]->header = image->header;
        images[i]->infoHeader = image->infoHeader;
        if(i == W - 1){
            images[i]->width = lastWidth;
        }else{
            images[i]->width = width;
        }
        images[i]->height = height;
        images[i]->pixels = (RGBPixel**) malloc(sizeof(RGBPixel*) * images[i]->height);

        for(int j = 0; j < images[i]->height; j++){
            images[i]->pixels[j] = (RGBPixel*) malloc(sizeof(RGBPixel) * images[i]->width);
        }
    }

    for(int i = 0; i < W; i++){
        for(int j = 0; j < images[i]->height; j++){
            for(int k = 0; k < images[i]->width; k++){
                images[i]->pixels[j][k] = image->pixels[j][k + (i * width)];
            }
        }
    }

    return images;
}


BMPImage *joinImage(BMPImage **images, int W){
    BMPImage *image = (BMPImage*) malloc(sizeof(BMPImage));
    image->header = images[0]->header;
    image->infoHeader = images[0]->infoHeader;
    image->width = images[0]->width * W;
    image->height = images[0]->height;
    image->pixels = (RGBPixel**) malloc(sizeof(RGBPixel*) * image->height);

    for(int i = 0; i < image->height; i++){
        image->pixels[i] = (RGBPixel*) malloc(sizeof(RGBPixel) * image->width);
    }

    for(int i = 0; i < W; i++){
        for(int j = 0; j < images[i]->height; j++){
            for(int k = 0; k < images[i]->width; k++){
                image->pixels[j][k + (i * images[i]->width)] = images[i]->pixels[j][k];
            }
        }
    }

    return image;
}


int nearlyBlack(BMPImage *image, float umbral){
    int count = 0;
    float percentage = 0;

    for(int i = 0; i < image->height; i++){
        for(int j = 0; j < image->width; j++){
            if(image->pixels[i][j].r == 0 && image->pixels[i][j].g == 0 && image->pixels[i][j].b == 0){
                count++;
            }
        }
    }

    float pixels = image->height * image->width;
    percentage = (count / pixels);

    if(percentage > umbral) return 1;
    else return 0;
}


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

BMPImage *binarizar(BMPImage *image, int umbral){
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
            if(image->pixels[i][j].r > umbral && image->pixels[i][j].g > umbral && image->pixels[i][j].b > umbral){
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

