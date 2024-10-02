#include "render.h"


// Entradas: la función render recibe:
//          - directory: Un puntero a una estructura dirent que representa un directorio.
//          - folder: Un puntero a una estructura DIR que representa un directorio.
//          - f: Un entero que representa la función que se quiere aplicar a las imágenes.
//          - p: Un número flotante que representa el factor de saturación.
//          - u: Un número flotante que representa el umbral de binarización.
//          - v: Un número flotante que representa el umbral de clasificación.
//          - N: Un puntero a un string que representa el prefijo de las imágenes a procesar.
//          - C: Un puntero a un string que representa el nombre de la carpeta donde se guardarán las imágenes resultantes.
//          - R: Un puntero a un string que representa el nombre del archivo csv donde se guardarán los resultados.
//          - resultFolder: Un puntero a un string que representa la carpeta donde se guardarán las imágenes resultantes.
// Salidas: la función no retorna nada, pero genera y guarda las imágenes resultantes en la carpeta resultFolder y guarda los resultados en el archivo csv R.
// Descripción: la función render se encarga de procesar las imágenes que se encuentran en un directorio, aplicando las funciones que se le indiquen y
//              pimero verifica si el nombre del archivo que contiene la imagen es valido.
void render(struct dirent *directory,DIR *folder, int f, float p,float u, float v, char *N, char *C, char *R, char *resultFolder){
    while(directory = readdir(folder)){
        if(strstr(directory->d_name, N) != NULL){
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


            BMPImage *image = readBMP(filename);
            if(f == 1){
                BMPImage *saturatedImage = saturar(image, p);
                strcat(saturatedName, directory->d_name);
                writeBMP(saturatedName, saturatedImage);

                FILE *csv = fopen(csvName, "a");

                int nB = nearlyBlack(saturatedImage, v);
                strcpy(finalName, "saturaded_");
                strcat(finalName, directory->d_name);
                if(nB==1){
                    fprintf(csv, "%s;%d", finalName, 1);
                    fputc('\n', csv);
                }else{
                    fprintf(csv, "%s;%d", finalName, 0);
                    fputc('\n', csv);
                }
                
                fclose(csv);

            }if(f == 2){
                BMPImage *saturatedImage = saturar(image, p);
                strcat(saturatedName, directory->d_name);
                writeBMP(saturatedName, saturatedImage);

                BMPImage *escalaGrisesImage = escalaGrises(image);
                strcat(grayName, directory->d_name);
                writeBMP(grayName, escalaGrisesImage);

                FILE *csv = fopen(csvName, "a");

                int nB = nearlyBlack(saturatedImage, v);
                strcpy(finalName, "saturaded_");
                strcat(finalName, directory->d_name);
                if(nB==1){
                    fprintf(csv, "%s;%d", finalName, 1);
                    fputc('\n', csv);
                }else{
                    fprintf(csv, "%s;%d", finalName, 0);
                    fputc('\n', csv);
                }

                nB = nearlyBlack(escalaGrisesImage, v);
                strcpy(finalName, "gray_");
                strcat(finalName, directory->d_name);
                if(nB==1){
                    fprintf(csv, "%s;%d", finalName, 1);
                    fputc('\n', csv);
                }else{
                    fprintf(csv, "%s;%d", finalName, 0);
                    fputc('\n', csv);
                }

                fclose(csv);

            }if(f == 3){
                BMPImage *saturatedImage = saturar(image, p);
                strcat(saturatedName, directory->d_name);
                writeBMP(saturatedName, saturatedImage);

                BMPImage *escalaGrisesImage = escalaGrises(image);
                strcat(grayName, directory->d_name);
                writeBMP(grayName, escalaGrisesImage);

                BMPImage *binarizedImage = binarizar(image, u);
                strcat(binarizedName, directory->d_name);
                writeBMP(binarizedName, binarizedImage);

                FILE *csv = fopen(csvName, "a");

                int nB = nearlyBlack(saturatedImage, v);
                strcpy(finalName, "saturaded_");
                strcat(finalName, directory->d_name);
                if(nB==1){
                    fprintf(csv, "%s;%d", finalName, 1);
                    fputc('\n', csv);
                }else{
                    fprintf(csv, "%s;%d", finalName, 0);
                    fputc('\n', csv);
                }

                nB = nearlyBlack(escalaGrisesImage, v);
                strcpy(finalName, "gray_");
                strcat(finalName, directory->d_name);
                if(nB==1){
                    fprintf(csv, "%s;%d", finalName, 1);
                    fputc('\n', csv);
                }else{
                    fprintf(csv, "%s;%d", finalName, 0);
                    fputc('\n', csv);
                }

                nB = nearlyBlack(binarizedImage, v);
                strcpy(finalName, "binarized_");
                strcat(finalName, directory->d_name);
                if(nB==1){
                    fprintf(csv, "%s;%d", finalName, 1);
                    fputc('\n', csv);
                }else{
                    fprintf(csv, "%s;%d", finalName, 0);
                    fputc('\n', csv);
                }

                fclose(csv);
            }
            printf("Se terminó de procesar la imagen: %s\n", filename);
        }
    }
}