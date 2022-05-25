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
        f=fopen("helpAll/et.help", "r");
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
    //on lit le fichier correspondant au chemin de l'image source une
    f=fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("[ il n'est pas possible d'ouvrir le premier fichier ]\n");
        exit(1);
    }
    char ch[5];
    fscanf(f, "%s\n", ch);
    if (strcmp(ch, "P1") != 0)
    {
        printf("[ la premiere image doit etre une image binaire ]\n");
        fclose(f);
        exit(1);
    }
    ImageB* img1 = read_B(f);
    fclose(f);
    
    //on cherche les chemins de destination
    char *dest1 = NULL;
    if (argv[3] == NULL)
    {
        char* current_dir = get_current_dir_name();
        if (current_dir == NULL)
        {
            free_ImageB(img1);
            exit(1);
        }
        i_file* info = info_file(argv[1]);
        dest1 = malloc((9+strlen(info->name)+strlen(current_dir))*sizeof(char));
        dest1[0]='\0';
        strcat(dest1,current_dir);
        strcat(dest1,"/");
        strcat(dest1,info->name);
        strcat(dest1,"-et.ppm");
        free(current_dir);
        free_i_file(info);
    }else{
        dest1 = malloc((1+strlen(argv[3]))*sizeof(char));
        strcpy(dest1, argv[3]);
    }
   
    // on charge la deuxieme image
    f = fopen(argv[2], "r");
    if (f == NULL)
    {
        free_ImageB(img1);
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }
    fscanf(f, "%s\n", ch);
    if (strcmp(ch, "P1") == 0)
    {
        ImageB * img2 = read_B(f);
        fclose(f);
        //on calcule le "et" entre les images
        if (img1->nLigne!= img2->nLigne || img1->nColonne!= img2->nColonne)
        {
            free_ImageB(img2);
            free_ImageB(img1);
            printf("[ les images non pas la meme dimension ]\n");
            exit(1);
        }
        ImageB *r = etB(img1, img2);
        //on libere les espaces
        free_ImageB(img2);
        free_ImageB(img1);
        
        //on sauvegarde
        if(dest1!=NULL){
            write_B(r,dest1);
            free(dest1);
        }
        free_ImageB(r);
    }
    else if (strcmp(ch, "P2") == 0)
    {
        ImageG *img2 = read_G(f);
        fclose(f);
        //on calcule le et logique
        if (img1->nLigne!= img2->nLigne || img1->nColonne!= img2->nColonne)
        {
            free_ImageG(img2);
            free_ImageB(img1);
            printf("[ les images non pas la meme dimension ]\n");
            exit(1);
        }
        ImageG *r = etG(img1, img2);
        //on libere les espaces
        free_ImageG(img2);
        free_ImageB(img1);
        
        //on sauvegarde
        if (dest1!=NULL)
        {
            write_G(r, dest1);
            free(dest1);
        }
    }
    else if (strcmp(ch, "P3") == 0)
    {
        free_ImageB(img1);
        printf("> pas encore pris en charge\n");
        fclose(f);
    }
    else
    {
        printf("[ format de fichier non pris en charge ]\n");
        free_ImageB(img1);
        if(dest1!=NULL){
            free(dest1);
        }
        fclose(f);
        exit(1);
    }
    return 0;
}
