#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../library/entete/Image.h"

int main(int argc, char const *argv[])
{
    
    Filtre* filtre = read_filtre(argv[2]);
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
        
        char * r_dest = (char *)malloc((15 + strlen(argv[1])) * sizeof(char));
        r_dest[0] = '\0';
        strcat(r_dest, argv[1]);
        strcat(r_dest, "_conv.pgm");
        
        
        ImageG *r = convolutionG(img, filtre);
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
