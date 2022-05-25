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
        f=fopen("helpAll/gradient.help", "r");
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
    if (strcmp(ch, "P1") == 0)
    {
        printf("> rien a faire \n");
        fclose(f);
    }
    else if (strcmp(ch, "P2") == 0)
    {
        ImageG *img = read_G(f);
        fclose(f);
        if (argv[2] == NULL)
        {
            printf("[ donnez le type de gradient ]\n");
            free_ImageG(img);
            exit(1);
        }
        int indicateur = -1;
        if (strcmp(argv[2], "sobel") == 0){
            indicateur = 0;
        }else if (strcmp(argv[2], "prewitt") == 0){
            indicateur = 1;
        }else{
            printf("[ le type de gradient n'est pas pris en charge ]\n");
            free_ImageG(img);
            exit(1);
        }
        
        //on cherche le chemin de destination 
        char *dest1 = NULL;
        if (argv[3] == NULL)
        {
            char* current_dir = get_current_dir_name();
            if (current_dir == NULL)
            {
                free_ImageG(img);
                exit(1);
            }
            i_file* info = info_file(argv[1]);
            dest1 = malloc((20+strlen(info->name)+strlen(current_dir))*sizeof(char));
            dest1[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info->name);
            strcat(dest1,"-gd(");
            if (indicateur==0){
                strcat(dest1,"sobel).pgm");
            }else if (indicateur== 1){
                strcat(dest1,"prewitt).pgm");
            }
            free_i_file(info);
            free(current_dir);
        }else{
            dest1 = malloc((1+strlen(argv[3]))*sizeof(char));
            strcpy(dest1, argv[3]);
        }
        if (dest1!=NULL)
        {
            Filtre* filtre1 = malloc(sizeof(Filtre));
            Filtre* filtre2 = malloc(sizeof(Filtre));
            filtre1->pas = 1;
            filtre2->pas = 1;
            filtre1->data = create_matrix(3,3);
            filtre2->data = create_matrix(3,3);
            if (indicateur==1)
            {
                filtre1->data[0][0]=-1;filtre1->data[0][1]=0;filtre1->data[0][2]=1;
                filtre1->data[1][0]=-1;filtre1->data[1][1]=0;filtre1->data[1][2]=1;
                filtre1->data[2][0]=-1;filtre1->data[2][1]=0;filtre1->data[2][2]=1;
                
                filtre2->data[0][0]=-1;filtre2->data[0][1]=-1;filtre2->data[0][2]=-1;
                filtre2->data[1][0]=0;filtre2->data[1][1]=0;filtre2->data[1][2]=0;
                filtre2->data[2][0]=1;filtre2->data[2][1]=1;filtre2->data[2][2]=1;
            }else if(indicateur==0){
                filtre1->data[0][0]=-1;filtre1->data[0][1]=0;filtre1->data[0][2]=1;
                filtre1->data[1][0]=-2;filtre1->data[1][1]=0;filtre1->data[1][2]=2;
                filtre1->data[2][0]=-1;filtre1->data[2][1]=0;filtre1->data[2][2]=1;
                
                filtre2->data[0][0]=-1;filtre2->data[0][1]=-2;filtre2->data[0][2]=-1;
                filtre2->data[1][0]=0;filtre2->data[1][1]=0;filtre2->data[1][2]=0;
                filtre2->data[2][0]=1;filtre2->data[2][1]=2;filtre2->data[2][2]=1;
            }
            printf("...");
            ImageG *r1 = convolutionG(img, filtre1);
            ImageG *r2 = convolutionG(img, filtre2);
            ImageG *r = plus_G(r1, r2);
            printf("\n");
            free_Filtre(filtre1);free_Filtre(filtre2);
            write_G(r, dest1);
            free_ImageG(r1);free_ImageG(r2);free_ImageG(r);
            free(dest1);
        }
        free_ImageG(img);
    }
    else if (strcmp(ch, "P3") == 0)
    {
        printf("> pas encre pris en charge \n");
        fclose(f);
    }
    else
    {
        printf("[ format de fichier non pris en charge ]\n");
        fclose(f);
        exit(1);
    }
    return 0;
}
