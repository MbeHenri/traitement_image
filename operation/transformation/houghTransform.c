#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "../../library/entete/Image.h"
#include "../../library/entete/file.h"
#include "../../library/entete/base.h"

int main(int argc, char const *argv[])
{
    //on verifie s'il ya au moins un parametre passé
    if (argv[1]==NULL || argc <1 )
    {
        exit(1);
    }
    FILE* f=NULL;
    // on verifie si le premier argument est --help ou -h 
    if (strcmp(argv[1], "--help")==0 || strcmp(argv[1], "-h")==0)
    {
        f=fopen("helpAll/houghTransform.help", "r");
        int car = 0;
        if (f != NULL)
        {
            // Boucle de lecture des caractères un à un
            do{
                car = fgetc(f);
                printf("%c", car);
            } while (car != EOF);
            printf("\n");
        }
        return 0;
    }
    //lecture du premier fichier
    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }
    char ch[5];
    fscanf(f, "%s\n", ch);
    if (strcmp(ch, "P1") != 0)
    {
        printf("[ l'image source doit etre une image binaire ]\n");
        fclose(f);
        exit(1);
    }
    ImageB *img = read_B(f);
    fclose(f);
    
    if (argv[2]==NULL)
    {
        free_ImageB(img);
        printf("[ le fichier des parametres n'as pas ete entré ]\n");
        fclose(f);
        exit(1);
    }
    f = fopen(argv[2], "r");
    if (f == NULL)
    {
        free_ImageB(img);
        printf("[ impossibilité d'ouvrir le fichier de parametres ]\n");
        exit(1);
    }
    double theta_min = 0, theta_max = 0, ecart_theta = 0,beta_min = 0, beta_max = 0, ecart_beta = 0;
    int color = 0;
    //on recupere les parametres des angles theta
    fscanf(f,"%lf", &theta_min);
    fscanf(f,"%lf", &theta_max);
    fscanf(f,"%lf", &ecart_theta);
    //on verifie si le min est different au maximum et que l'ecart est strictement positif 
    if (theta_min == theta_max || ecart_theta <=0)
    {
        free_ImageB(img);
        fclose(f);
        printf("[ les paramettres de beta sont mal entrés ]\n");
        exit(1);
    }
    //on recupere les parametres des reels beta
    fscanf(f,"%lf", &beta_min);
    fscanf(f,"%lf", &beta_max);
    fscanf(f,"%lf", &ecart_beta);
    //on verifie si le min est different au maximum et que l'ecart est strictement positif 
    if (theta_min == theta_max || ecart_theta <=0)
    {
        free_ImageB(img);
        fclose(f);
        printf("[ impossibilité d'ouvrir le fichier de parametres ]\n");
        exit(1);
    }
    fscanf(f,"%d", &color);
    //on verifie que la couleur a prendre est soit 1 pour noir et 0 pour blanc
    if (color!=0 && color!=1)
    {
        free_ImageB(img);
        fclose(f);
        printf("[ la couleur donnee dans les parametres n'est pas pris en charge ]\n");
        exit(1);
    }
    fclose(f);
    if (theta_min > theta_max)
    {
        int aux = theta_max;
        theta_max = theta_min;
        theta_min = aux;
    }
    if (beta_min > beta_max)
    {
        int aux = beta_max;
        beta_max = beta_min;
        beta_min = aux;
    }
    if (argv[3]==NULL)
    {
        free_ImageB(img);
        printf("[ le nombre de droites n'as pas donné ]\n");
        exit(1);
    }
    int K = 0;K=atoi(argv[3]);
    if (K<=0)
    {
        free_ImageB(img);
        printf("[ le nombre de droites n'est pas strictement positif ]\n");
        exit(1);
    }
    
    Vector_d* theta = echantillonage(theta_min,theta_max,ecart_theta);
    Vector_d* beta = echantillonage(beta_min, beta_max, ecart_beta);
    //on cherche le chemin de destination 
    char *dest1 = NULL;
    char *dest2 = NULL;
    if (argv[4] == NULL)
    {
        char* current_dir = get_current_dir_name();
        if (current_dir == NULL)
        {
            free_ImageB(img);
            free_vector_d(theta);
            free_vector_d(beta);
            exit(1);
        }
        i_file* info = info_file(argv[1]);
        i_file* info1 = info_file(argv[2]);
        dest1 = malloc((15+strlen(info->name)+strlen(info1->name)+strlen(current_dir)+strlen(info1->name))*sizeof(char));
        dest2 = malloc((15+strlen(info->name)+strlen(info1->name)+strlen(argv[3])+strlen(current_dir)+strlen(info1->name))*sizeof(char));
        dest1[0]='\0';
        dest2[0]='\0';
        strcat(dest1,current_dir);
        strcat(dest1,"/");
        strcat(dest1,info->name);
        strcat(dest1,"-hough(");
        strcat(dest1,info1->name);
        strcat(dest1,").pgm");
        
        strcat(dest2,current_dir);
        strcat(dest2,"/");
        strcat(dest2,info->name);
        strcat(dest2,"-hough(");
        strcat(dest2,info1->name);
        strcat(dest2,"-");
        strcat(dest2,argv[3]);
        strcat(dest2,").txt");
        free_i_file(info);
        free_i_file(info1);
        free(current_dir);
    }else{
        dest1 = malloc((1+strlen(argv[4]))*sizeof(char));
        strcpy(dest1, argv[4]);
        if (argv[5]!=NULL)
        {
            dest2 = malloc((1+strlen(argv[5]))*sizeof(char));
            strcpy(dest2, argv[5]);
        }
    }
    //calculde la transformé de hough
    printf("...");
    int ** hough = transform_hough_occur(img, beta, theta, color);
    printf("\n");
    if (dest1!= NULL)
    {
        printf("...");
        ImageG* r = convert_matrixG(hough, beta->n, theta->n);
        write_G(r, dest1);
        free(dest1);
        free_ImageG(r);
        printf("\n");
    }
    if (dest2!= NULL)
    {
        printf("...");
        int** kmax = selection_k_max(hough,beta->n, theta->n, K);
        int i=0,x1=0,y1=0,x2=0,y2=0;
        double angle = 0;
        f =fopen(dest2, "w");
        fprintf(f, "%d\n", K);
        for (i = 0; i < K ; i++){
            angle = PI*theta->data[kmax[i][1]]/180;
            if (cos(angle)==0)
            {
                x1=0; x2=theta->n-1;
                y1=beta->data[kmax[i][0]]/sin(angle); y2=y1;
            }else if(sin(angle)==0)
            {
                y1=0; y2=beta->n-1;
                x1=beta->data[kmax[i][0]]/cos(angle); x2=x1;
            }else{
                x1=0; y1=beta->data[kmax[i][0]]/sin(angle);
                x2=theta->n-1; y2= (beta->data[kmax[i][0]]-x2*cos(angle))/sin(angle);
            }
            fprintf(f, "%d;%d;%d;%d\n",x1,y1,x2,y2);
        }
        fclose(f);
        free_matrix(kmax,K);
        free(dest2);
        printf("\n");
    }
    free_ImageB(img);
    free_matrix(hough, beta->n);
    free_vector_d(theta);
    free_vector_d(beta);
    return 0;
}
