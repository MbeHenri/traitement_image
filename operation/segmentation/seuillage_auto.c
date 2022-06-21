#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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
        f=fopen("helpAll/seuillage_auto.help", "r");
        int car = 0;
        if (f != NULL)
        {
            // Boucle de lecture des caractères un à un
            do{
                car = fgetc(f);
                printf("%c", car);
            } while (car != EOF);
            printf("\n");
            fclose(f);
        }
        return 0;
    }
    //lecture du premier fichier
    f = fopen(argv[1], "r");
    if (f == NULL){
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }
    char ch[5];
    fscanf(f, "%s\n", ch);
    if( strcmp(ch, "P1") == 0){
        printf("> pas encore pris en charge \n");
        fclose(f);
    }else if (strcmp(ch, "P2") == 0)
    {
        ImageG * img = read_G(f);
        fclose(f);
        
        //on cherche le chemin de destination 
        char *dest1 = NULL;
        if (argv[2] == NULL)
        {
            char* current_dir = get_current_dir_name();
            if (current_dir == NULL)
            {
                free_ImageG(img);
                exit(1);
            }
            i_file* info1 = info_file(argv[1]);
            
            dest1 = malloc((15+strlen(info1->name)+strlen(current_dir))*sizeof(char));
            dest1[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info1->name);
            strcat(dest1,"-sauto.pgm");
            free(current_dir);
            free_i_file(info1);
        }else{
            dest1 = malloc((1+strlen(argv[2]))*sizeof(char));
            strcpy(dest1, argv[2]);
        }
        // et on sauvegarde
        if(dest1!=NULL){
            ImageG* r = seuillage_auto_otsuG(img);
            write_G(r,dest1);
            free_ImageG(r);
            free(dest1);
        }
        free_ImageG(img);
    }else if( strcmp(ch, "P3") == 0){
        printf(">pas encore pris en charge \n");
        fclose(f);
    }else{
        printf("[ format de fichier non pris en charge ]\n");
        fclose(f);
        exit(1);
    }
    
    return 0;
}
