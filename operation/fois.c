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
        f=fopen("helpAll/fois.help", "r");
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
        ImageG *imgd = read_G(f);
        fclose(f);
        //on recupere le ratio
        if (argv[2]==NULL)
        {
            printf("[ le ration n'as pas été donné ]\n");
            exit(1);
        }
        double ratio = atof(argv[2]);
        //on calcule le fois
        ImageG *img = fois_G(imgd, ratio);
        //on libere
        free_ImageG(imgd);
        
        //on cherche le chemin de destination 
        char *dest1 = NULL;
        if (argv[3] == NULL)
        {
            char* current_dir = get_current_dir_name();
            if (current_dir == NULL)
            {
                exit(1);
            }
            i_file* info = info_file(argv[1]);
            dest1 = malloc((15+strlen(info->name)+strlen(argv[2])+strlen(current_dir))*sizeof(char));
            dest1[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info->name);
            strcat(dest1,"-fois(");
            strcat(dest1,argv[2]);
            strcat(dest1,").pgm");
            free(current_dir);
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
        printf("> premiere image: image a couleur \n");
        printf("[ rien a faire ]\n");
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
