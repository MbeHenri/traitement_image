#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "../library/entete/Image.h"
#include "../library/entete/file.h"

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
        f=fopen("helpAll/plus.help", "r");
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
        printf("> rien a faire\n");
        fclose(f);
    }
    else if (strcmp(ch, "P2") == 0)
    {
        ImageG *img1 = read_G(f);
        fclose(f);
        
        //lecture du deuxieme fichier
        f = fopen(argv[2], "r");
        if (f == NULL)
        {
            printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
            exit(1);
        }
        char ch[5];
        fscanf(f, "%s\n", ch);
        if (strcmp(ch, "P2") != 0)
        {
            printf("[ le deuxieme fichier n'est pas une image a niveau de gris ]\n");
            fclose(f);
            free_ImageG(img1);
            exit(1);
        }
        ImageG *img2 = read_G(f);
        fclose(f);
        //calcul du plus
        ImageG *img = plus_G(img1, img2);
        //libearation
        free_ImageG(img1);
        free_ImageG(img2);

        //on cherche le chemin de destination 
        char *dest1 = NULL;
        if (argv[3] == NULL)
        {
            char* current_dir = get_current_dir_name();
            if (current_dir == NULL)
            {
                exit(1);
            }
            i_file* info1 = info_file(argv[1]);
            i_file* info2 = info_file(argv[2]);
            
            dest1 = malloc((14+strlen(info1->name)+strlen(info2->name)+strlen(current_dir))*sizeof(char));
            dest1[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info1->name);
            strcat(dest1,"-plus-");
            strcat(dest1,info2->name);
            strcat(dest1,".pgm");
        }else{
            dest1 = malloc((1+strlen(argv[3]))*sizeof(char));
            strcpy(dest1, argv[3]);
        }
        // et on sauvegarde
        if(dest1!=NULL){
            write_G(img,dest1);
            free(dest1);
        }
        free_ImageG(img);
    }
    else if (strcmp(ch, "P3") == 0)
    {
        printf("> rien a faire \n");
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
