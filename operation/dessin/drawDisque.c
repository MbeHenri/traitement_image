#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../library/entete/Image.h"

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
        
        unsigned int xr = atoi(argv[2]), yr = atoi(argv[3]);
        double rayon = atof(argv[4]);
        if( xr >= img->nColonne || yr >= img->nLigne ){
            free_ImageG(img);
            printf("[ un des points ne se trouve pas dans l'image (les coordonnees ne correspondent pas) ]\n");
            exit(1);
        }
        
        int val_replace  = 0;
        if(argv[5]!=NULL){
            val_replace = atoi(argv[6]);
            if (val_replace > 255)
            {
                val_replace = 255;
            }
        }
        
        /* TRACER DU DISQUE
        */
        char * r_dest = (char *)malloc((17 + strlen(argv[1])) * sizeof(char));
        r_dest[0] = '\0';
        strcat(r_dest, argv[1]);
        strcat(r_dest, "_with_disque.pgm");
        
        ImageG *r = drawDisqueG(img, xr,yr, rayon, val_replace);      
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
