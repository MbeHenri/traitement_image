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
        unsigned int pas = 0;
        pas = atoi(argv[2]);
        if (pas == 0)
        {
            free_ImageG(img);
            printf("[ le pas n'as pas ete donne ]\n");
            exit(1);
        }
        
        ImageG *r = convolutionMedianG(img, pas);
        char * r_dest = (char *)malloc((10 + strlen(argv[1])) * sizeof(char));
        r_dest[0] = '\0';
        strcat(r_dest, argv[1]);
        strcat(r_dest, "_convM.pgm");
        
        write_G(r, r_dest);
        free_ImageG(r);
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
