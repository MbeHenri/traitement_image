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
        f=fopen("helpAll/kmeans.help", "r");
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
    //on recupere la premiere image
    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }
    char ch[5];
    fscanf(f, "%s\n", ch);
    if( strcmp(ch, "P1") == 0){
        printf("> rien a faire \n");
        fclose(f);
    }else if (strcmp(ch, "P2") == 0)
    {
        ImageG * img = read_G(f);
        fclose(f);
        if (argv[2] == NULL || argv[3]==NULL || argv[4]==NULL)
        {
            free_ImageG(img);
            printf("[ entrez les parametres importants a savoir le nombre de clusters, les seuil de convergences de centres et d'inertie intra-classe ]\n");
            exit(1);
        }
        int K=0;K=atoi(argv[2]);
        double e1 =0; e1=atof(argv[3]);
        double e2 =0; e2=atof(argv[4]);
        if (K<=0 || e1<=0 || e2<=0)
        {
            free_ImageG(img);
            printf("[ les parametres doivent etre positives ]\n");
            exit(1);
        }
        //on cherche le chemin de destination 
        char *dest1 = NULL;
        if (argv[5] == NULL)
        {
            char* current_dir = get_current_dir_name();
            if (current_dir == NULL)
            {
                free_ImageG(img);
                exit(1);
            }
            i_file* info = info_file(argv[1]);
            dest1 = malloc((16+strlen(info->name)+strlen(argv[2])+strlen(current_dir))*sizeof(char));
            dest1[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info->name);
            strcat(dest1,"-(");
            strcat(dest1,argv[2]);
            strcat(dest1,")means.pgm");
            free_i_file(info);
            free(current_dir);
        }else{
            dest1 = malloc((1+strlen(argv[5]))*sizeof(char));
            strcpy(dest1, argv[5]);
        }
        if (dest1!=NULL)
        {
            ImageG* r = kmeansG(img, K,e1,e2);
            write_G(r, dest1);
            free_ImageG(r);
            free(dest1);
        }
        free_ImageG(img);
    }else if( strcmp(ch, "P3") == 0){
        printf("> pas encore pris en charge \n");
        fclose(f);
    }else{
        printf("[ format de fichier non pris en charge ]\n");
        fclose(f);
        exit(1);
    }
    return 0;
}
