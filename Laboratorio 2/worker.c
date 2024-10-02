#include "fworker.h"

int main(int argc, char **argv){

    int fd[2];
    int fd2[2];
    int filter;
    float p;
    float u;

    fd[1] = atoi(argv[1]);
    fd[0] = atoi(argv[2]);
    fd2[1] = atoi(argv[3]);
    fd2[0] = atoi(argv[4]);
    filter = atoi(argv[5]);
    p = atof(argv[6]);
    u = atof(argv[7]);

    BMPHeader headerBuffer;
    BMPInfoHeader infoHeaderBuffer;
    int heightBuffer;
    int widthBuffer;

    close(fd[1]);
    read(fd[0], &headerBuffer, sizeof(BMPHeader));
    read(fd[0], &infoHeaderBuffer, sizeof(BMPInfoHeader));
    read(fd[0], &heightBuffer, sizeof(int));
    read(fd[0], &widthBuffer, sizeof(int));

    RGBPixel **pixelsBuffer = malloc(sizeof(RGBPixel*)*heightBuffer);
    for(int j = 0; j < heightBuffer; j++){
    pixelsBuffer[j] = malloc(sizeof(RGBPixel)*widthBuffer);
    read(fd[0], pixelsBuffer[j], sizeof(RGBPixel)*widthBuffer);
    }

    BMPImage *image = malloc(sizeof(BMPImage));
    image->header = headerBuffer;
    image->infoHeader = infoHeaderBuffer;
    image->height = heightBuffer;
    image->width = widthBuffer;
    image->pixels = pixelsBuffer;

    BMPImage *auxImage = malloc(sizeof(BMPImage));

    
        BMPImage *auxImage = saturar(image, p);
    
                    
    // Envio la imagen saturada
    BMPHeader headerBuffer2 = auxImage->header;
    BMPInfoHeader infoHeaderBuffer2 = auxImage->infoHeader;
    RGBPixel **pixelsBuffer2 = auxImage->pixels;
    int heightBuffer2 = auxImage->height;
    int widthBuffer2 = auxImage->width;

    close(fd2[0]);
    write(fd2[1], &headerBuffer2, sizeof(BMPHeader));
    write(fd2[1], &infoHeaderBuffer2, sizeof(BMPInfoHeader));
    write(fd2[1], &heightBuffer2, sizeof(int));
    write(fd2[1], &widthBuffer2, sizeof(int));
    for(int j = 0; j < heightBuffer2; j++){
        write(fd2[1], pixelsBuffer2[j], sizeof(RGBPixel)*widthBuffer2);
    }

    printf("Worker terminado\n");

    exit(0);
}