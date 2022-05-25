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
        f=fopen("helpAll/drawLines.help", "r");
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
        if (argv[2]==NULL || argv[3]==NULL)
        {
            free_ImageG(img);
            printf("[ les parametres du rectangles ne sont pas utilisables ]\n");
            exit(1);
        }
        //on recupere les parametres utiles
        int couleur=-1;
        couleur= atoi(argv[3]);
        if(  couleur<0 || couleur>255){
            free_ImageG(img);
            printf("[ la couleur doit etre compris dans 0..255 ]\n");
            exit(1);
        }
        //on cherche les chemins de destination 
        char *dest1 = NULL;
        if (argv[4] == NULL)
        {
            char* current_dir = get_current_dir_name();
            if (current_dir == NULL)
            {
                free_ImageG(img);
                exit(1);
            }
            i_file* info = info_file(argv[1]);
            i_file* info1 = info_file(argv[2]);
            dest1 = malloc((17+strlen(info->name)+strlen(info1->name)+strlen(argv[3])+strlen(current_dir))*sizeof(char));
            dest1[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info->name);
            strcat(dest1,"-avec(");
            strcat(dest1,info1->name);
            strcat(dest1,"*");
            strcat(dest1, argv[3]);
            strcat(dest1,").pgm");
            
            free(current_dir);
            free_i_file(info);
        }else{
            dest1 = malloc((1+strlen(argv[4]))*sizeof(char));
            strcpy(dest1, argv[4]);
        }
        /* TRACER DU RECTANGLE)
         */
        if (dest1!=NULL)
        {
            f = fopen(argv[2], "r");
            if (f==NULL)
            {
                free_ImageG(img);
                free(dest1);
                printf("[ impossible d'ouvrir le fichiers contenant les segments ]\n");
                exit(1);
            }
            int n = 0;
            fscanf(f,"%d",&n);
            if (n<=0)
            {
                free_ImageG(img);
                free(dest1);
                printf("[ le nombre de segments est incorrect ]\n");
                exit(1);
            }
            int i=0;
            int ** segments = create_matrix(n,4);
            for (i = 0; i < n; i++)
                fscanf(f,"%d;%d;%d;%d",&segments[i][0],&segments[i][1],&segments[i][2],&segments[i][3]);
            fclose(f);
            for (i = 0; i < n; i++)
                draw_segmentG(img,segments[i][0],segments[i][1],segments[i][2],segments[i][3],couleur);
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
