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
        f=fopen("helpAll/inverse.help", "r");
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
        f = fopen(argv[2], "r");
        if (f == NULL)
        {
            free_ImageG(img);
            printf("[ il est impossible d'ouvrir le chemin du fichier des segments ]\n");
            exit(1);
        }
        int len = 0;
        fscanf(f, "%d", &len);
        if (len < 1)
        {
            free_ImageG(img);
            printf("[ mauvais nombre de segment ]\n");
            fclose(f);
            exit(1);
        }
        int *s = malloc(len * sizeof(int));
        int *v = malloc(len * sizeof(int));
        int i = 0, j=0;
        for (i = 0; i < len; i++){
            fscanf(f, "%d", &s[i]);
            if(s[i]<=0 || s[i]>=255){
                free(s);
                free(v);
                printf("[ un des segments n'est pas compris strictement entre 0 et 255 ]\n");
                free_ImageG(img);
                fclose(f);
                exit(1);
            }
            for ( j = 0; j < i; j++)
            {
                if (s[i]==s[j])
                {
                    free(s);
                    free(v);
                    printf("[ il as occurence de segment ]\n");
                    free_ImageG(img);
                    fclose(f);
                    exit(1);
                }
            }
        }
        for (i = 0; i < len; i++){
            fscanf(f, "%d", &v[i]);
            if(v[i] <= 0 || v[i] >= 255){
                free(s);
                free(v);
                printf("[ un des segment n'est pas compris strictement entre 0 et 255 ]\n");
                free_ImageG(img);
                fclose(f);
                exit(1);
            }
            for ( j = 0; j < i; j++)
            {
                if (v[i]==v[j])
                {
                    free(s);
                    free(v);
                    printf("[ il as occurence de segment ]\n");
                    free_ImageG(img);
                    fclose(f);
                    exit(1);
                }
            }
        }
        fclose(f);
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
            i_file* info1 = info_file(argv[2]);
            dest1 = malloc((15+strlen(info->name)+strlen(current_dir)+strlen(info1->name))*sizeof(char));
            dest1[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info->name);
            strcat(dest1,"-tlm(");
            strcat(dest1,info1->name);
            strcat(dest1,").pgm");
            free_i_file(info);
            free_i_file(info1);
            free(current_dir);
        }else{
            dest1 = malloc((1+strlen(argv[3]))*sizeof(char));
            strcpy(dest1, argv[3]);
        }
        if (dest1!=NULL)
        {
            printf("0/100\n");
            ImageG *r = transform_lineaire_morceau_G(img, s, v, len);
            printf("100/100\n");
            write_G(r, dest1);
            free(dest1);
        }
        free_ImageG(img);
    }
    else if (strcmp(ch, "P3") == 0)
    {
        printf("> pas encore pris en charge\n");
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
