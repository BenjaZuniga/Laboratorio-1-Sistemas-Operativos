#include "fbroker.h"

#include <string.h>
#include <wait.h>

int main(int argc, char **argv){
    int f = atoi(argv[2]);
    float p = atof(argv[4]);
    float u = atof(argv[6]);
    float v = atof(argv[8]);
    char *N = argv[10];
    char *C = argv[12];
    char *R = argv[14];
    int W = atoi(argv[16]);

    char *resultFolder = malloc(200); // Carpeta de resultados
    char *auxName = malloc(200); // Nombre auxiliar
    DIR *folderImages, *folder; // Carpeta de imagenes
    struct dirent *directory; // Imagenes de la carpeta
    
    strcpy(auxName, R); // Nombre del archivo de clasificación
    strcat(auxName, ".csv"); // Se le agrega ".csv" para que sea un archivo csv
    remove(auxName); // Elimina el archivo csv con los resultados si ya existe
    
    rmdir(C); // Elimina la carpeta de resultados si ya existe
    mkdir(C, 0755); // Crea la carpeta de resultados

    strcat(resultFolder, C); // Nombre de resultados
    strcat(resultFolder, "/"); // Se le agrega "/" para que sea una dirección

    folderImages = opendir("./Imagenes_Iniciales"); // Abre la carpeta actual
    folder = opendir(".");

    while(directory = readdir(folderImages)){
        if(strstr(directory->d_name, N) != NULL){
            int actualFilter = 1;
            int i = 0;
            int check = 0;
            if(strstr(directory->d_name, "imagen_") != NULL){
                i=7;
            }else if(strstr(directory->d_name, "img_") != NULL){
                i=4;
            }else if(strstr(directory->d_name, "photo_") != NULL){
                i=6;
            }
            for(i; i<strlen(directory->d_name); i++){
                if(directory->d_name[i] == '.'){
                    break;
                }else if(atoi(&directory->d_name[i])==0 && !isdigit(directory->d_name[i])){
                    check = 1;
                    break;
                }
            }
            if(check == 1){
                printf("El archivo %s no tiene un nombre valido\n", directory->d_name);
                continue;
            }

            printf("Se está procesando la imagen: %s\n", directory->d_name);
            char *filename = malloc(200);
            char *saturatedName = malloc(200);
            char *grayName = malloc(200);
            char *binarizedName = malloc(200);
            char *finalName = malloc(200);
            char *csvName = malloc(200);

            strcpy(csvName, R);
            strcat(csvName, ".csv");

            strcpy(filename, "./Imagenes_Iniciales/");
            strcat(filename, directory->d_name);

            strcpy(saturatedName, resultFolder);
            strcat(saturatedName, "saturated_");

            strcpy(grayName, resultFolder);
            strcat(grayName, "gray_");

            strcpy(binarizedName, resultFolder);
            strcat(binarizedName, "binarized_");

            for(actualFilter; actualFilter <= f; actualFilter++){
                // Creo los pipes 
                int fd[W][2];
                int fd2[W][2];

                for(int i = 0; i < W; i++){
                    pipe(fd[i]);
                    pipe(fd2[i]);
                }

                BMPImage *imageaux = readBMP(filename);
                BMPImage **images = splitImage(imageaux, W);
                BMPImage **saturatedImages = malloc(sizeof(BMPImage*)*W);
                int pids[W];
            
                for(int i = 0; i < W; i++){ 
                    pids[i] = fork();
                    if(pids[i] == 0){ // Hijo
                        char filterToApply[15], fdI1string[10], fdI0string[10], fd2I1string[10], fd2I0string[10];
                        char pstring[10], ustring[10];
                        snprintf(filterToApply, sizeof(filterToApply), "%d", actualFilter);
                        snprintf(fdI1string, sizeof(fdI1string), "%d", fd[i][1]);
                        snprintf(fdI0string, sizeof(fdI0string), "%d", fd[i][0]);
                        snprintf(fd2I1string, sizeof(fd2I1string), "%d", fd2[i][1]);
                        snprintf(fd2I0string, sizeof(fd2I0string), "%d", fd2[i][0]);
                        snprintf(pstring, sizeof(pstring), "%.2f", p);
                        snprintf(ustring, sizeof(ustring), "%.2f", u);


                        char *argv2[] = {"./worker", fdI1string, fdI0string, fd2I1string, fd2I0string, filterToApply, pstring, ustring, NULL};

                        execv("./worker", argv2);
                        /*BMPHeader headerBuffer;
                        BMPInfoHeader infoHeaderBuffer;
                        int heightBuffer;
                        int widthBuffer;

                        close(fd[i][1]);
                        read(fd[i][0], &headerBuffer, sizeof(BMPHeader));
                        read(fd[i][0], &infoHeaderBuffer, sizeof(BMPInfoHeader));
                        read(fd[i][0], &heightBuffer, sizeof(int));
                        read(fd[i][0], &widthBuffer, sizeof(int));

                        RGBPixel **pixelsBuffer = malloc(sizeof(RGBPixel*)*heightBuffer);
                        for(int j = 0; j < heightBuffer; j++){
                            pixelsBuffer[j] = malloc(sizeof(RGBPixel)*widthBuffer);
                            read(fd[i][0], pixelsBuffer[j], sizeof(RGBPixel)*widthBuffer);
                        }

                        BMPImage *image = malloc(sizeof(BMPImage));
                        image->header = headerBuffer;
                        image->infoHeader = infoHeaderBuffer;
                        image->height = heightBuffer;
                        image->width = widthBuffer;
                        image->pixels = pixelsBuffer;

                        // Saturo la imagen
                        BMPImage *saturatedImage = saturar(image, p);
                        
                        // Envio la imagen saturada
                        BMPHeader headerBuffer2 = saturatedImage->header;
                        BMPInfoHeader infoHeaderBuffer2 = saturatedImage->infoHeader;
                        RGBPixel **pixelsBuffer2 = saturatedImage->pixels;
                        int heightBuffer2 = saturatedImage->height;
                        int widthBuffer2 = saturatedImage->width;

                        close(fd2[i][0]);
                        write(fd2[i][1], &headerBuffer2, sizeof(BMPHeader));
                        write(fd2[i][1], &infoHeaderBuffer2, sizeof(BMPInfoHeader));
                        write(fd2[i][1], &heightBuffer2, sizeof(int));
                        write(fd2[i][1], &widthBuffer2, sizeof(int));
                        for(int j = 0; j < heightBuffer2; j++){
                            write(fd2[i][1], pixelsBuffer2[j], sizeof(RGBPixel)*widthBuffer2);
                        }

                        exit(0);*/
                    } else{ // Padre    
                        BMPHeader headerBuffer = images[i]->header;
                        BMPInfoHeader infoHeaderBuffer = images[i]->infoHeader;
                        RGBPixel **pixelsBuffer = images[i]->pixels;
                        int heightBuffer = images[i]->height;
                        int widthBuffer = images[i]->width;

                        close(fd[i][0]);
                        write(fd[i][1], &headerBuffer, sizeof(BMPHeader));
                        write(fd[i][1], &infoHeaderBuffer, sizeof(BMPInfoHeader));
                        write(fd[i][1], &heightBuffer, sizeof(int));
                        write(fd[i][1], &widthBuffer, sizeof(int));
                        for(int j = 0; j < heightBuffer; j++){
                            write(fd[i][1], pixelsBuffer[j], sizeof(RGBPixel)*widthBuffer);
                        }

                        // recibo la imagen saturada
                        BMPHeader headerBuffer2;
                        BMPInfoHeader infoHeaderBuffer2;
                        int heightBuffer2;
                        int widthBuffer2;
                        
                        close(fd2[i][1]);
                        read(fd2[i][0], &headerBuffer2, sizeof(BMPHeader));
                        read(fd2[i][0], &infoHeaderBuffer2, sizeof(BMPInfoHeader));
                        read(fd2[i][0], &heightBuffer2, sizeof(int));
                        read(fd2[i][0], &widthBuffer2, sizeof(int));

                        RGBPixel **pixelsBuffer2 = malloc(sizeof(RGBPixel*)*heightBuffer2);
                        for(int j = 0; j < heightBuffer2; j++){
                            pixelsBuffer2[j] = malloc(sizeof(RGBPixel)*widthBuffer2);
                            read(fd2[i][0], pixelsBuffer2[j], sizeof(RGBPixel)*widthBuffer2);
                        }

                        BMPImage *saturatedImage = malloc(sizeof(BMPImage));
                        saturatedImage->header = headerBuffer2;
                        saturatedImage->infoHeader = infoHeaderBuffer2;
                        saturatedImage->height = heightBuffer2;
                        saturatedImage->width = widthBuffer2;
                        saturatedImage->pixels = pixelsBuffer2;

                        // Guardo la imagen saturada
                        saturatedImages[i] = saturatedImage;
                    }
                }

                // Espero a que terminen los procesos hijos
                for(int i = 0; i < W; i++){
                    waitpid(pids[i], NULL, 0);
                }


                BMPImage *finalImage = joinImage(saturatedImages, W);
                if(actualFilter == 1){
                    strcat(saturatedName, directory->d_name);
                    writeBMP(saturatedName, finalImage);
                }else if(actualFilter == 2){
                    strcat(grayName, directory->d_name);
                    writeBMP(grayName, finalImage);
                }else if(actualFilter == 3){
                    strcat(binarizedName, directory->d_name);
                    writeBMP(binarizedName, finalImage);
                }
            }

    
            /*
            if (pid == 0){
                BMPHeader headerBuffer;
                BMPInfoHeader infoHeaderBuffer;
                int heightBuffer;
                int widthBuffer;
                RGBPixel **pixelsBuffer;

                close(fd[0][1]);
                read(fd[0][0], &headerBuffer, sizeof(BMPHeader));
                read(fd[0][0], &infoHeaderBuffer, sizeof(BMPInfoHeader));
                read(fd[0][0], &heightBuffer, sizeof(int));
                read(fd[0][0], &widthBuffer, sizeof(int));
                pixelsBuffer = malloc(sizeof(RGBPixel*)*heightBuffer);
                for(int i = 0; i < heightBuffer; i++){
                    pixelsBuffer[i] = malloc(sizeof(RGBPixel)*widthBuffer);
                    read(fd[0][0], pixelsBuffer[i], sizeof(RGBPixel)*widthBuffer);
                }

                // imprimo la altura y el ancho de la imagen
                printf("Height: %d\n", heightBuffer);
                printf("Width: %d\n", widthBuffer);

                // Imprimo los valores del primer pixel
                printf("R: %d\n", pixelsBuffer[0][0].r);
                printf("G: %d\n", pixelsBuffer[0][0].g);
                printf("B: %d\n", pixelsBuffer[0][0].b);

                BMPImage *image = malloc(sizeof(BMPImage));
                image->header = headerBuffer;
                image->infoHeader = infoHeaderBuffer;
                image->height = heightBuffer;
                image->width = widthBuffer;
                image->pixels = pixelsBuffer;

                BMPImage *saturatedImage = saturar(image, p);
                strcat(saturatedName, directory->d_name);
                writeBMP(saturatedName, saturatedImage);
            
                exit(0);
            } else{
                BMPImage *image = images[0];
                BMPHeader headerBuffer = image->header;
                BMPInfoHeader infoHeaderBuffer = image->infoHeader;
                RGBPixel **pixelsBuffer = image->pixels;
                int heightBuffer = image->height;
                int widthBuffer = image->width;

                close(fd[0][0]);
                write(fd[0][1], &headerBuffer, sizeof(BMPHeader));
                write(fd[0][1], &infoHeaderBuffer, sizeof(BMPInfoHeader));
                write(fd[0][1], &heightBuffer, sizeof(int));
                write(fd[0][1], &widthBuffer, sizeof(int));
                for(int i = 0; i < heightBuffer; i++){
                    write(fd[0][1], pixelsBuffer[i], sizeof(RGBPixel)*widthBuffer);
                }

                // imprimo la altura y el ancho de la imagen
                printf("Padre-> Height: %d\n", heightBuffer);
                printf("Padre-> Width: %d\n", widthBuffer);
                
                // Imprimo los valores del primer pixel
                printf("Padre-> R: %d\n", pixelsBuffer[0][0].r);
                printf("Padre-> G: %d\n", pixelsBuffer[0][0].g);
                printf("Padre-> B: %d\n", pixelsBuffer[0][0].b);

            }

            waitpid(pid, NULL, 0);
            */
            /*
            int pid;
            pid = fork();
            if(pid == 0){ // Worker
                BMPHeader headerBuffer;
                BMPInfoHeader infoHeaderBuffer;
                int heightBuffer;
                int widthBuffer;
                RGBPixel **pixelsBuffer;

                close(fd[0][1]);
                read(fd[0][0], &headerBuffer, sizeof(BMPHeader));
                read(fd[0][0], &infoHeaderBuffer, sizeof(BMPInfoHeader));
                read(fd[0][0], &heightBuffer, sizeof(int));
                read(fd[0][0], &widthBuffer, sizeof(int));
                pixelsBuffer = malloc(sizeof(RGBPixel*)*heightBuffer);
                for(int i = 0; i < heightBuffer; i++){
                    pixelsBuffer[i] = malloc(sizeof(RGBPixel)*widthBuffer);
                    read(fd[0][0], pixelsBuffer[i], sizeof(RGBPixel)*widthBuffer);
                }

                // imprimo la altura y el ancho de la imagen
                printf("Height: %d\n", heightBuffer);
                printf("Width: %d\n", widthBuffer);

                // Imprimo los valores del primer pixel
                printf("R: %d\n", pixelsBuffer[0][0].r);
                printf("G: %d\n", pixelsBuffer[0][0].g);
                printf("B: %d\n", pixelsBuffer[0][0].b);

                BMPImage *image = malloc(sizeof(BMPImage));
                image->header = headerBuffer;
                image->infoHeader = infoHeaderBuffer;
                image->height = heightBuffer;
                image->width = widthBuffer;
                image->pixels = pixelsBuffer;

                BMPImage *saturatedImage = saturar(image, p);
                strcat(saturatedName, directory->d_name);
                writeBMP(saturatedName, saturatedImage);
            
                exit(0);
            }else{ // Broker
                BMPImage *image = readBMP(filename);
                BMPHeader headerBuffer = image->header;
                BMPInfoHeader infoHeaderBuffer = image->infoHeader;
                RGBPixel **pixelsBuffer = image->pixels;
                int heightBuffer = image->height;
                int widthBuffer = image->width;

                close(fd[0][0]);
                write(fd[0][1], &headerBuffer, sizeof(BMPHeader));
                write(fd[0][1], &infoHeaderBuffer, sizeof(BMPInfoHeader));
                write(fd[0][1], &heightBuffer, sizeof(int));
                write(fd[0][1], &widthBuffer, sizeof(int));
                for(int i = 0; i < heightBuffer; i++){
                    write(fd[0][1], pixelsBuffer[i], sizeof(RGBPixel)*widthBuffer);
                }

                // imprimo la altura y el ancho de la imagen
                printf("Padre-> Height: %d\n", heightBuffer);
                printf("Padre-> Width: %d\n", widthBuffer);
                
                // Imprimo los valores del primer pixel
                printf("Padre-> R: %d\n", pixelsBuffer[0][0].r);
                printf("Padre-> G: %d\n", pixelsBuffer[0][0].g);
                printf("Padre-> B: %d\n", pixelsBuffer[0][0].b);
            }

            waitpid(pid, NULL, 0);
            */
        }
    }

    return 0;
}