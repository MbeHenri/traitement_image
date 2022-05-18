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
        printf(">  premiere image: image binaire \n");
        printf("[ rien a faire ]\n");
        fclose(f);
    }
    else if (strcmp(ch, "P2") == 0)
    {

        printf(">multiplication d'une image a niveau de gris par un ratio \n");
        ImageG *imgd = read_G(f);
        fclose(f);
        double ratio = atof(argv[2]);

        // on contruit l'image destination
        char *dest = "./fois_res.pgm\0";
        if (argv[3] != NULL)
        {
            dest = (char *)malloc((1 + strlen(argv[3])) * sizeof(char));
            dest[0] = '\0';
            strcat(dest, argv[3]);
        }
        ImageG *img = fois_G(imgd, ratio);
        free_ImageG(imgd);
        write_G(img, dest);
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
