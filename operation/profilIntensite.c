#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../library/entete/Image.h"

int main(int argc, char const *argv[])
{
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }

    char ch[5];
    fscanf(f, "%s\n", ch);

    if (strcmp(ch, "P1") == 0)
    {
        printf("> image binaire \n");
        printf("[ rien a faire ]\n");
        fclose(f);
    }
    else if (strcmp(ch, "P2") == 0)
    {
        printf(">image a niveau de gris \n");
        ImageG *img = read_G(f);
        fclose(f);
        
        unsigned int x1 = atoi(argv[2]), y1 = atoi(argv[3]), x2 = atoi(argv[4]), y2 = atoi(argv[5]);
        if( x1 >= img->nColonne || x2 >= img->nColonne || y1 >= img->nLigne || y2 >= img->nLigne ){
            free_ImageG(img);
            printf("[ un des points ne se trouve pas dans l'image (les coordonnees ne correspondent pas) ]\n");
            exit(1);
        }
        
        int val_replace  = 0;
        if(argv[6]!=NULL){
            val_replace = atoi(argv[6]);
            if (val_replace > 255)
            {
                val_replace = 255;
            }
        }
        /* OBTENTION DU VECTEUR DU PROFIL D'INTENSITE 
        */
        // on contruit l'image destination
        char * dest = (char *)malloc((12 + strlen(argv[1])) * sizeof(char));
        dest[0] = '\0';
        strcat(dest, argv[1]);
        strcat(dest, "_profil.txt");
        
        Vector* v = profil_intensite_G(img, x1,y1,x2,y2);
        f = fopen(dest , "w");
        if (f == NULL){
            exit(1);
        }
        unsigned int i=0;
        fprintf(f, "thon\n");
        for ( i = 0; i < v->n; i++)
            fprintf(f, "%d\n", v->data[i] );
        fclose(f);
        free_vector(v);
        
        /* OBTENTION DE L'IMAGE AVEC LA DROITE (OU ENCORE LE SEGMENT)
        */
        char * r_dest = (char *)malloc((15 + strlen(argv[1])) * sizeof(char));
        r_dest[0] = '\0';
        strcat(r_dest, argv[1]);
        strcat(r_dest, "_with_line.pgm");
        ImageG *r = draw_segmentG(img, x1,y1, x2,y2, val_replace);      
        write_G(r, r_dest);
        
        free_ImageG(img);
        free_ImageG(r);
        
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
