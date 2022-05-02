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

    if (strcmp(ch, "P1") != 0)
    {
        printf("[ la premiere image doit etre une image binaire ]\n");
        fclose(f);
        exit(1);
    }
    ImageB *img = read_B(f);
    fclose(f);

    double theta_min = atof(argv[2]), theta_max = atof(argv[3]), ecart_theta = atof(argv[4]);
    double beta_min = atof(argv[5]), beta_max = atof(argv[6]), ecart_beta = atof(argv[7]);
    
    int color = 0;
    if (argv[8]!=NULL)
    {
        if (strcmp(ch, "noir") != 0)
        {
            color = 1;
        }
    }
    Vector_d* theta = echantillonage(theta_min,theta_max,ecart_theta);
    Vector_d* beta = echantillonage(beta_min, beta_max, ecart_beta);
    
    int ** hough = transform_hough_occur(img, beta, theta, color);
    ImageG* r = convert_matrixG(hough, beta->n, theta->n);
    
    char * r_dest = (char *)malloc((11 + strlen(argv[1])) * sizeof(char));
    r_dest[0] = '\0';
    strcat(r_dest, argv[1]);
    strcat(r_dest, "_hough.pgm");
    
    write_G(r, r_dest);
    free_ImageG(r);
    free_ImageB(img);
    
    return 0;
}
