#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../library/entete/Image.h"
#include "../../library/entete/base.h"

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

        int i = 0, j = 0, nLigne = 0, nCol = 0;
        Complex **spec = spectre_fourier(img, &nLigne, &nCol);
        double d;
        double **aux = create_matrix_d(nLigne, nCol);
        for (i = 0; i < nLigne; i++)
        {
            for (j = 0; j < nCol; j++)
            {
                d = log(1+ norme_complex(spec[i][j]));
                if (i<nLigne/2 && j<nCol/2)
                    aux[nLigne/2-i-1][nCol/2-j-1]= d;
                else if(i<nLigne/2 && j>=nCol/2)
                    aux[nLigne/2-i-1][3*nCol/2-j-1]=d;
                else if(i>=nLigne/2 && j<nCol/2)
                    aux[3*nLigne/2-i-1][nCol/2-j-1]=d;
                else 
                    aux[3*nLigne/2-i-1][3*nCol/2-j-1]=d;
            }
        }     
        free_matrix_complex(spec, nLigne, nCol);
        double **norm = norm_matrix_d(aux, nLigne, nCol);
        free_matrix_d(aux, nLigne);

        int **val = create_matrix(nLigne, nCol);
        for (i = 0; i < nLigne; i++)
            for (j = 0; j < nCol; j++)
                val[i][j] = norm[i][j] * 255;

        free_matrix_d(norm, nLigne);
        img = convert_matrixG(val, nLigne, nCol);
        free_matrix(val, nLigne);

        write_G(img, argv[2]);
        free_ImageG(img);
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
