#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../entete/Image.h"

void free_ImageG(ImageG* img){
    int i=0;
    for ( i = 0; i < img->nLigne; i++)
        free(img->data[i]);
    free(img->data);
    free(img);
}

ImageG * read_G(FILE * f){
    ImageG * img = (ImageG *) malloc(sizeof(ImageG));
    if ( img == NULL){
        printf("[ il est impossible d'allouer de la memoire pour l'image ]\n");
        exit(1);
    }
    while (fgetc(f) == '#' )
    {
        while (getc(f)!='\n');
    }
    fseek(f, -1, SEEK_CUR);
    
    fscanf(f, "%d %d", &img->nLigne, &img->nColonne);
    img->data = (unsigned int **) malloc(img->nLigne*sizeof(unsigned int*));
    if ( img->data == NULL){
        printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels ]\n");
        exit(1);
    }
    int i=0, j=0;
    for (i=0; i<img->nLigne; i++){
        img->data[i]=(unsigned int *) malloc(img->nColonne*sizeof(unsigned int)); 
        if ( img->data[i] == NULL){
            printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels ]\n");
            exit(1);
        }
    }
    for (i = 0; i < img->nLigne; i++)
        for (j = 0; j < img->nColonne; j++)
            fscanf(f, "%d", &img->data[i][j]);
            
    return img;
}

unsigned int * histogram_G(ImageG * img){
    unsigned int * hist = (unsigned int *)malloc( 255 * sizeof(unsigned int));
    if (hist == NULL){
       printf("[ impossible d'allouer de la memoire pour l'histogramme ]\n");
       exit(1);
    }
    unsigned int i=0,j=0;
    for ( i = 0; i < 256; i++)
        hist[i] = 0;
        
    for ( i = 0; i < img->nLigne; i++)
        for ( j = 0; j < img->nColonne; j++)
            hist[img->data[i][j]]++;
    
    return hist;
}

double luminance_G(ImageG* img){
    unsigned int sum=0;
    unsigned int i=0, j=0;
    for ( i = 0; i < img->nLigne; i++)
        for ( j = 0; j < img->nColonne; j++)
            sum += img->data[i][j];
    
    return sum / (img->nColonne * img->nLigne);
}
unsigned int max_G(ImageG * img){
    unsigned int m = 0, i=0, j=0;
    for ( i = 0; i < img->nLigne; i++)
        for ( j = 0; j < img->nColonne; j++)
            if(img->data[i][j] > m)
                m = img->data[i][j];
    return m;
}
unsigned int min_G(ImageG * img){
    unsigned int m = 255, i=0, j=0;
    for ( i = 0; i < img->nLigne; i++)
        for ( j = 0; j < img->nColonne; j++)
            if(img->data[i][j] < m)
                m = img->data[i][j];
    return m;
}
double contraste_ecart_type_G(ImageG * img){
    unsigned int i=0,j=0;
    double moy = luminance_G(img);
    double result = 0; 
    for ( i = 0; i < img->nLigne; i++){
        for ( j = 0; j < img->nColonne; j++){
            result += pow((double) (img->data[i][j]) - moy, 2.0);
        }
    }
    result /= img->nColonne*img->nLigne;
    return sqrt(result);
}
double contraste_min_max_G(ImageG * img){
    unsigned int  min = min_G(img) , max = max_G(img);
    return ((double)(max-min))/(max+min);
}

ImageG* plus(ImageG* img1, ImageG* img2){
    if ( img1->nLigne != img2->nLigne && img1->nColonne != img2->nColonne)
    {
        printf(" [ les images n'ont pas la meme dimension ]\n");
        exit(1);
    }
    ImageG * img = (ImageG *) malloc(sizeof(ImageG));
    if ( img == NULL){
        printf("[ il est impossible d'allouer de la memoire pour l'image resultante ]\n");
        exit(1);
    }
    img->nLigne = img1->nLigne; img->nColonne = img1->nColonne;
    img->data = (unsigned int **) malloc(img->nLigne*sizeof(unsigned int*));
    if ( img->data == NULL){
        printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels resultants]\n");
        exit(1);
    }
    int i=0, j=0;
    for (i=0; i<img->nLigne; i++){
        img->data[i]=(unsigned int *) malloc(img->nColonne*sizeof(unsigned int)); 
        if ( img->data[i] == NULL){
            printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels resultants]\n");
            exit(1);
        }
    }
    
    for ( i = 0; i < img->nLigne; i++){
        for ( j = 0; j < img->nColonne; j++){
            img->data[i][j] = img1->data[i][j] + img2->data[i][j];
            if(img->data[i][j] > 255)
                img->data[i][j] = 255;
        }
    }
    return img;
}
ImageG* fois(ImageG* imgd ,double ratio ){
    ImageG * img = (ImageG *) malloc(sizeof(ImageG));
    if ( img == NULL){
        printf("[ il est impossible d'allouer de la memoire pour l'image resultante ]\n");
        exit(1);
    }
    img->nLigne = img1->nLigne; img->nColonne = img1->nColonne;
    img->data = (unsigned int **) malloc(img->nLigne*sizeof(unsigned int*));
    if ( img->data == NULL){
        printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels resultants]\n");
        exit(1);
    }
    int i=0, j=0;
    for (i=0; i<img->nLigne; i++){
        img->data[i]=(unsigned int *) malloc(img->nColonne*sizeof(unsigned int)); 
        if ( img->data[i] == NULL){
            printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels resultants]\n");
            exit(1);
        }
    }
    
    for ( i = 0; i < img->nLigne; i++){
        for ( j = 0; j < img->nColonne; j++){
            img->data[i][j] = (unsigned int)(ratio * img1->data[i][j]);
            if(img->data[i][j] > 255)
                img->data[i][j] = 255;
            if(img->data[i][j] < 0)
                img->data[i][j] = 0;
        }
    }
    return img;
}
ImageG* moins(ImageG* img1, ImageG* img2){
    if ( img1->nLigne != img2->nLigne && img1->nColonne != img2->nColonne){
        printf(" [ les images n'ont pas la meme dimension ]\n");
        exit(1);
    }
    ImageG * img = (ImageG *) malloc(sizeof(ImageG));
    if ( img == NULL){
        printf("[ il est impossible d'allouer de la memoire pour l'image resultante ]\n");
        exit(1);
    }
    img->nLigne = img1->nLigne; img->nColonne = img1->nColonne;
    img->data = (unsigned int **) malloc(img->nLigne*sizeof(unsigned int*));
    if ( img->data == NULL){
        printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels resultants]\n");
        exit(1);
    }
    int i=0, j=0;
    for (i=0; i<img->nLigne; i++){
        img->data[i]=(unsigned int *) malloc(img->nColonne*sizeof(unsigned int)); 
        if ( img->data[i] == NULL){
            printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels resultants]\n");
            exit(1);
        }
    }
    int v;
    for ( i = 0; i < img->nLigne; i++){
        for ( j = 0; j < img->nColonne; j++){
            v = img1->data[i][j] - img2->data[i][j];
            if(v < 0){
                img->data[i][j] = 0;
            }else{
                img->data[i][j] = (unsigned int) v;
            }
        }
    }
    return img;
}

Vector* profil_intensite(ImageG* img, unsigned int x1 , unsigned int y1, unsigned int x2, unsigned int y2 ){
    if ( img->nLigne <= y1 && img->nLigne <= y2 && img->nColonne <= x1 && img->nColonne <= x2){
        printf(" [ les positions de pixels ne correspondent pas aux images ]\n");
        exit(1);
    }
    unsigned int x,y,v, max=0, min = 0;
    Vector* result = NULL;
    if (x1 == x2){
        max = y1;
        min = y2;
        if (max < y2){
            min = y1;
            max = y2;
        }
        result = (Vector *) malloc((max - min + 1)*sizeof(Vector));
        if (result == NULL){
            printf(" [ un probleme d'allocation de memoire est survenu ]\n");
            exit(1);
        }
        result->data = (unsigned int *) malloc((max - min + 1)*sizeof(unsigned int));
        if (result->data == NULL){
            printf(" [ un probleme d'allocation de memoire est survenu ]\n");
            exit(1);
        }
        for (y = min; y <= max; y++)
            result->data[y - min] = img->data[y][x2];
    }else{
        max = x1;
        min = x2;
        if (max < x2){
            min = x1;
            max = x2;
        }
        result = (Vector *) malloc((max - min + 1)*sizeof(Vector));
        if (result == NULL){
            printf(" [ un probleme d'allocation de memoire est survenu ]\n");
            exit(1);
        }
        result->data = (unsigned int *) malloc((max - min + 1)*sizeof(unsigned int));
        if (result->data == NULL){
            printf(" [ un probleme d'allocation de memoire est survenu ]\n");
            exit(1);
        }
        for (x = min; x <= max; x++)
            result->data[x - min] = img->data[( (y2 - y1)/(x2 - x1) )*(x - x1) + y1][x]; 
    }
    return result;
}