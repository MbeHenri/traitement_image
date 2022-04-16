#include <stdio.h>
#include <stdlib.h>

#include "../entete/base.h"

int **transform_linear(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int **result = create_matrix(n_ligne, n_col);
    int min = min_(d, n_ligne, n_col), max = max_(d, n_ligne, n_col);
    unsigned int i, j;
    int LUT[256];
    for (i = 0; i < n_ligne; i++)
        LUT[i] = (int)( (255 * (d[i][j] - min)) / (max - min) );
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            result[i][j] = LUT[d[i][j]];
            if (result[i][j] < 0)
                result[i][j] = 0 if (result[i][j] > 255)
                    result[i][j] = 255
        }
    }
    return result;
}
int **transform_linear_satur(int **d, unsigned int n_ligne, unsigned int n_col, int c_min, int c_max)
{
    int **result = create_matrix(n_ligne, n_col);
    unsigned int i, j;
    int LUT[256];
    for (i = 0; i < n_ligne; i++)
        LUT[i] = (int)( (255 * (d[i][j] - c_min)) / (c_max - c_min) );
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            result[i][j] = LUT[d[i][j]];
            if (result[i][j] < 0)
                result[i][j] = 0 if (result[i][j] > 255)
                    result[i][j] = 255
        }
    }
    return result;
}

int **egalizer_hist(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int **result = create_matrix(n_ligne, n_col);
    int *hist = histogram(d, n_ligne, n_col);
    double c[256] = {0};
    int i = 0;
    for (i = 0; i <= 255; i++)
    {
        if (i == 0)
        {
            c[i] = hist[0] / (n_ligne * n_col);
        }
        else
        {
            c[i] = c[i - 1] + hist[i] / (n_ligne * n_col);
        }
    }
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            result[i][j]= (int)( c[d[i][j]]*255 );
}