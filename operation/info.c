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
        printf(">pas encore pris en charge \n");
        fclose(f);
    }
    else if (strcmp(ch, "P2") == 0)
    {
        ImageG *img = read_G(f);
        fclose(f);

        int max = max_G(img), min = min_G(img), h=img->nLigne,w=img->nColonne;
        double contraste_ecart_type = contraste_ecart_type_G(img);
        double contraste_min_max = contraste_min_max_G(img);
        double lum = luminance_G(img);
        //on libere
        free_ImageG(img);
        //on cherche le chemin de destination 
        char *dest1 = NULL;
        if (argv[2] == NULL)
        {
            char* current_dir = get_current_dir_name();
            if (current_dir == NULL)
            {
                exit(1);
            }
            i_file* info = info_file(argv[1]);
            dest1 = malloc((12+strlen(info->name)+strlen(current_dir))*sizeof(char));
            dest1[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info->name);
            strcat(dest1,"-info.txt");
            free(current_dir);
        }else{
            dest1 = malloc((1+strlen(argv[2]))*sizeof(char));
            strcpy(dest1, argv[2]);
        }
        // et on sauvegarde
        if(dest1!=NULL){
            f = fopen(dest1,"w");
            if (f==NULL)
            {
                exit(1);
            }
            fprintf(f,"hauteur:%d\n",h);
            fprintf(f,"largeur:%d\n",w);
            fprintf(f,"max:%d\n",max);
            fprintf(f,"min:%d\n",min);
            fprintf(f,"max:%d\n",max);
            fprintf(f,"contraste min-max:%f\n",contraste_min_max);
            fprintf(f,"contraste ecart-type:%f\n",contraste_ecart_type);
            fprintf(f,"luminance:%f\n",lum);
            fclose(f);
        }
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
