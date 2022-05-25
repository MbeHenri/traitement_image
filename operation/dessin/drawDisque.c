#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "../../library/entete/Image.h"
#include "../../library/entete/file.h"

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
        f=fopen("helpAll/drawDisque.help", "r");
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
        printf("> pas encore pris en charge \n");
        fclose(f);
    }
    else if (strcmp(ch, "P2") == 0)
    {
        ImageG *img = read_G(f);
        fclose(f);
        if (argv[2]==NULL || argv[3]==NULL || argv[4]==NULL || argv[5]==NULL)
        {
            free_ImageG(img);
            printf("[ le format de parametres n'as pas ete repecteé ]\n");
            exit(1);
        }
        //on recupere les parametres utiles
        int x1 = 0, y1 = 0,couleur=-1;
        double rayon = 0;
        x1 = atoi(argv[2]); y1 = atoi(argv[3]); rayon = atof(argv[4]);couleur= atoi(argv[5]);
        if( x1 >= img->nColonne || x1<0 || rayon <=0 || y1 >= img->nLigne || y1<0 || couleur<0 || couleur>255){
            free_ImageG(img);
            printf("[ les paramtres du rectangles ne sont pas utilisables ]\n");
            exit(1);
        }
        
        //on cherche les chemins de destination 
        char *dest1 = NULL;
        if (argv[6] == NULL)
        {
            char* current_dir = get_current_dir_name();
            if (current_dir == NULL)
            {
                free_ImageG(img);
                exit(1);
            }
            char* segment_str = malloc((4+strlen(argv[2])+strlen(argv[3])+strlen(argv[4]))*sizeof(char));
            segment_str[0]='\0';
            strcat(segment_str, argv[2]);
            strcat(segment_str, "-");
            strcat(segment_str, argv[3]);
            strcat(segment_str, "*");
            strcat(segment_str, argv[4]);
            
            i_file* info = info_file(argv[1]);
            dest1 = malloc((15+strlen(info->name)+strlen(segment_str)+strlen(current_dir))*sizeof(char));
            dest1[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info->name);
            strcat(dest1,"-avec(");
            strcat(dest1, segment_str);
            strcat(dest1,").pgm");
            free(segment_str);
            free(current_dir);
            free_i_file(info);
        }else{
            dest1 = malloc((1+strlen(argv[6]))*sizeof(char));
            strcpy(dest1, argv[6]);
        }
        /* TRACER DU DISQUE
         */
        if (dest1!=NULL)
        {
            drawDisqueG(img, x1, y1,rayon, couleur);
            write_G(img, dest1);
            free(dest1);
        }
        free_ImageG(img);
    }
    else if (strcmp(ch, "P3") == 0)
    {
        printf("> pas encore pris en charge \n");
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
