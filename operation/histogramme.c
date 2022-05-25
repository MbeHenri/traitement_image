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
        f=fopen("helpAll/histogramme.help", "r");
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
    
    //on lit le fichier correspondant au chemin de l'image source 
    f=fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }
    char ch[5];
    fscanf(f, "%s\n", ch);
    
    //on verifie si l'image donné est bien au format de fichier ascii ppm pbm ou pgm 
    if (strcmp(ch, "P1") == 0)
    {
        printf("> pas encore pris en charge \n");
        fclose(f);
    }
    else if (strcmp(ch, "P2") == 0)
    {
        // on lit les donnees de l'image
        ImageG *img = read_G(f);
        fclose(f);
        
        //on recherche l'histogramme
        int *hist = histogram_G(img);
        free_ImageG(img);
        ImageC* aux = histogrameGC(hist, 256);
        
        //on cherche les chemins de destination 
        char *dest1 = NULL;
        char* dest2 = NULL;
        if (argv[2] == NULL)
        {
            char* current_dir = get_current_dir_name();
            if (current_dir == NULL)
            {
                free(hist);
                free_ImageC(aux);
                exit(1);
            }
            i_file* info = info_file(argv[1]);
            dest1 = malloc((11+strlen(info->name)+strlen(current_dir))*sizeof(char));
            dest2 = malloc((11+strlen(info->name)+strlen(current_dir))*sizeof(char));
            dest1[0]='\0';
            dest2[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info->name);
            strcat(dest1,"-hist.ppm");
            
            strcat(dest2,current_dir);
            strcat(dest2,"/");
            strcat(dest2,info->name);
            strcat(dest2,"-hist.txt");
            
            free_i_file(info);
            free(current_dir);
        }else{
            dest1 = malloc((1+strlen(argv[2]))*sizeof(char));
            strcpy(dest1, argv[2]);
            if (argv[3]!=NULL){
                dest2 = malloc((1+strlen(argv[3]))*sizeof(char));
                strcpy(dest2, argv[3]);
            }
        }
        // et on sauvegarde
        if(dest1!=NULL){
            write_C(aux,dest1);
            free(dest1);
        }
        if(dest2!=NULL){
            f = fopen(dest2, "w");
            int i= 0;
            for (i = 0; i < 256; i++)
                fprintf(f,"%d,%d\n",i, hist[i]);
            fclose(f);
            free(dest2);
        }
        free(hist);
        free_ImageC(aux);
    }
    else if (strcmp(ch, "P3") == 0)
    {
        printf("> Les images couleurs ne sont pas encore pris en charge \n");
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
