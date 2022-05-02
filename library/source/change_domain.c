#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../entete/base.h"
#include "../entete/change_domain.h"

int **transformer_hough(int **d, unsigned int n_ligne, unsigned int n_col, double *beta, unsigned int len_beta, double *theta, unsigned int len_theta, int color)
{
    int **result = create_matrix(len_beta, len_theta);
    unsigned int i, j, t;

    for (i = 0; i < len_beta; i++)
        for (j = 0; j < len_theta; j++)
            result[i][j] = 0;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {

            if (d[i][j] == color)
            {

                for (t = 0; t < len_theta; t++)
                {
                    const double aux = j * cos(theta[t]) + i * sin(theta[t]);
                    const int ind = indice_val_proche(beta, len_beta, aux);
                    if (ind > 0)
                    {
                        result[ind][t]++;
                    }
                }
            }
        }
    }
    return result;
}
int **transform_fourier_reelle(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int **result = create_matrix(n_ligne, n_col);
    unsigned int i, j, p, q;
    for (p = 0; p < n_ligne; p++)
    {
        for (q = 0; q < n_col; q++)
        {
            result[p][q] = 0;
            for ( i = 0; i < n_ligne; i++)
                for ( j = 0; j < n_col; j++)
                    result[p][q] += d[i][j] * cos(360*( (p*i)/n_ligne + (q*j)/n_col));
        }
    }
    return result;
}
int **transform_fourier_imaginaire(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int **result = create_matrix(n_ligne, n_col);
    unsigned int i, j, p, q;
    for (p = 0; p < n_ligne; p++)
    {
        for (q = 0; q < n_col; q++)
        {
            result[p][q] = 0;
            for ( i = 0; i < n_ligne; i++)
                for ( j = 0; j < n_col; j++)
                    result[p][q] -= d[i][j] * sin(360*( (p*i)/n_ligne + (q*j)/n_col)); 
        }
    }
    return result;
}