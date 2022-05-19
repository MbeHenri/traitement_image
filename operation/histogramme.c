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
        printf("> Image binaire \n");

        fclose(f);
    }
    else if (strcmp(ch, "P2") == 0)
    {
        printf("> Image a niveau de gris \n");
        ImageG *img = read_G(f);
        fclose(f);

        int *hist = histogram_G(img);
        free_ImageG(img);

        char *dest = (char *)malloc((12 + strlen(argv[1])) * sizeof(char));
        dest[0] = '\0';
        strcat(dest, argv[1]);
        strcat(dest, "hist");

        f = fopen(dest, "w");
        if (f == NULL)
        {
            printf("fdgdfg\n");
            exit(1);
        }

        int i = 0;
        fprintf(f, "couleur,occurence\n");
        for (i = 0; i < 256; i++)
            fprintf(f, "%d,%d\n", i, hist[i]);
        
        strcat(dest, "c.ppm");
        ImageC* aux = histogrameC(hist, 256);
        write_C(aux,dest);
        free_ImageC(aux);
        
        printf("// histogramme de %s est dans le fichier %s\n", argv[1], dest);
        fclose(f);
    }
    else if (strcmp(ch, "P3") == 0)
    {
        printf("> Image a couleur \n");

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
