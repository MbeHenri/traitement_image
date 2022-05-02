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
        printf("[ rien a faire ]\n");
        fclose(f);
    }
    else if (strcmp(ch, "P2") == 0)
    {

        printf("> construction du spectre de fourier \n");
        ImageG *img = read_G(f);
        fclose(f);
        int** rez_m = matrix_spectre_fourier_reelle(img);
        int** img_m = matrix_spectre_fourier_imaginaire(img);
        
        ImageG* img_rez = convert_matrixG(rez_m, img->nLigne, img->nColonne);
        ImageG* img_img = convert_matrixG(img_m, img->nLigne, img->nColonne);
        
        write_G(img_rez, argv[2]);
        write_G(img_img, argv[3]);
        free_ImageG(img);
        free_ImageG(img_rez);
        free_ImageG(img_img);
    }
    else if (strcmp(ch, "P3") == 0)
    {
        printf("> construction du spectre de fourier \n");
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
