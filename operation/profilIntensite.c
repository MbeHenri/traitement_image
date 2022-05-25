#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "../library/entete/Image.h"
#include "../library/entete/file.h"
#include "../library/entete/base.h"

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
        f=fopen("helpAll/profilIntensite.help", "r");
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
        printf("> pas encore pris en charge\n");
        fclose(f);
    }
    else if (strcmp(ch, "P2") == 0)
    {                            
        ImageG *img = read_G(f);
        fclose(f);
        if (argv[2]==NULL || argv[3]==NULL || argv[4]==NULL || argv[5]==NULL)
        {
            free_ImageG(img);
            printf("[ les coordonnees des points d'extremite du segment du segment ]\n");
            exit(1);
        }
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        x1 = atoi(argv[2]); y1 = atoi(argv[3]); x2 = atoi(argv[4]); y2 = atoi(argv[5]);
        if( x1 >= img->nColonne || x1<0 || x2 >= img->nColonne || x2 <0 || y1 >= img->nLigne || y1<0 || y2 >= img->nLigne || y2 <0 ){
            free_ImageG(img);
            printf("[ un des points ne se trouve pas dans l'image (les coordonnees ne correspondent pas) ]\n");
            exit(1);
        }
        int n = 0,moy=0,ligne=255;
        int** v = profil_intensite_G(img, x1,y1,x2,y2,&n);
        moy = moy_v(v[0],n);
        if (moy>128)
            ligne=0;
        draw_segmentG(img, x1,y1, x2,y2,ligne);
        //on cherche les chemins de destination 
        char *dest1 = NULL;
        char* dest2 = NULL;
        char* dest3 = NULL;
        if (argv[6] == NULL)
        {
            char* current_dir = get_current_dir_name();
            if (current_dir == NULL)
            {
                free_ImageG(img);
                free_matrix(v,3);
                exit(1);
            }
            char* segment_str = malloc((4+strlen(argv[2])+strlen(argv[3])+strlen(argv[4])+strlen(argv[5]))*sizeof(char));
            segment_str[0]='\0';
            strcat(segment_str, argv[2]);
            strcat(segment_str, "-");
            strcat(segment_str, argv[3]);
            strcat(segment_str, "-");
            strcat(segment_str, argv[4]);
            strcat(segment_str, "-");
            strcat(segment_str, argv[5]);
            
            i_file* info = info_file(argv[1]);
            dest1 = malloc((17+strlen(info->name)+strlen(segment_str)+strlen(current_dir))*sizeof(char));
            dest2 = malloc((17+strlen(info->name)+strlen(segment_str)+strlen(current_dir))*sizeof(char));
            dest3 = malloc((15+strlen(info->name)+strlen(segment_str)+strlen(current_dir))*sizeof(char));
            dest1[0]='\0';
            dest2[0]='\0';
            dest3[0]='\0';
            strcat(dest1,current_dir);
            strcat(dest1,"/");
            strcat(dest1,info->name);
            strcat(dest1,"-profil(");
            strcat(dest1, segment_str);
            strcat(dest1,").ppm");
            
            strcat(dest2,current_dir);
            strcat(dest2,"/");
            strcat(dest2,info->name);
            strcat(dest2,"-profil(");
            strcat(dest2, segment_str);
            strcat(dest2,").txt");
            
            strcat(dest3,current_dir);
            strcat(dest3,"/");
            strcat(dest3,info->name);
            strcat(dest3,"-avec(");
            strcat(dest3, segment_str);
            strcat(dest3,").ppm");
            free(segment_str);
            free(current_dir);
            free_i_file(info);
        }else{
            dest1 = malloc((1+strlen(argv[6]))*sizeof(char));
            strcpy(dest1, argv[6]);
            if (argv[7]!=NULL){
                dest2 = malloc((1+strlen(argv[7]))*sizeof(char));
                strcpy(dest2, argv[7]);
                if (argv[8]!=NULL){
                    dest3 = malloc((1+strlen(argv[8]))*sizeof(char));
                    strcpy(dest2, argv[8]);
                }
            }
        }
        if (dest3 != NULL)
        {
            write_G(img, dest3);
            free(dest3);
        }
        free_ImageG(img);
        if (dest1 != NULL)
        {
            ImageC* profilImg = profilGC(v[0],n);
            write_C(profilImg, dest1);
            free_ImageC(profilImg);
            free(dest1);
        }
        if (dest2 != NULL)
        {
            f = fopen(dest2 , "w");
            if (f == NULL){
                exit(1);
            }
            int i=0;
            fprintf(f, "x;y;val\n");
            for ( i = 0; i < n; i++)
                fprintf(f,"%d;%d;%d\n", v[1][i], v[2][i], v[0][i]);
            fclose(f);  
            free(dest2);
        }
        free_matrix(v, 3);
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
