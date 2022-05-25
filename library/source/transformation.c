#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "../entete/base.h"
#include "../entete/transformation.h"

int **transform_linear(int **d, int n_ligne, int n_col)
{
    int **result = create_matrix(n_ligne, n_col);
    int min = min_(d, n_ligne, n_col), max = max_(d, n_ligne, n_col);
    int i, j;
    int LUT[256];
    for (i = 0; i < 256; i++)
        LUT[i] = (255 * (i - min)) / (max - min);

    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            result[i][j] = LUT[d[i][j]];
    return result;
}
int **transform_linear_satur(int **d, int n_ligne, int n_col, int c_min, int c_max)
{
    int **result = create_matrix(n_ligne, n_col);
    int i, j;
    int LUT[256];

    for (i = 0; i < 256; i++)
    {
        LUT[i] = (255 * (i - c_min)) / (c_max - c_min);
        if (LUT[i] < 0)
            LUT[i] = 0;
        if (LUT[i] > 255)
            LUT[i] = 255;
    }

    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            result[i][j] = LUT[d[i][j]];
    return result;
}
int **transform_linear_morceau(int **d, int n_ligne, int n_col, int *s, int *v, int len)
{
    int **result = changer_plage(d, n_ligne, n_col, 0, s[0], 0, v[0]);
    int i;
    int ind = 0, j = 0;
    int LUT[256];
    for (i = 0; i < 256; i++)
    {
        if (ind < len && i >= s[ind])
            ind++;

        if (ind == 0)
        {
            LUT[i] = v[0] * (i-s[0]) / s[0] + v[0];
        }
        else if (ind >= len)
        {
            LUT[i] = (255 - v[ind - 1]) * (i - 255) / (255 - s[ind - 1]) + 255;
        }
        else
        {
            LUT[i] = (v[ind] - v[ind - 1]) * (i - s[ind]) / (s[ind] - s[ind - 1])+v[ind];
        }
    }
    for (ind = 0; ind < n_ligne; ind++)
        for (j = 0; j < n_col; j++)
            result[ind][j] = LUT[d[ind][j]];
    return result;
}
int **egalizer_hist(int **d, int n_ligne, int n_col)
{
    int **result = create_matrix(n_ligne, n_col);
    int *hist = histogram(d, n_ligne, n_col);
    int n = n_ligne * n_col;
    double *c = malloc(256 * sizeof(double));
    int i = 0;
    for (i = 0; i < 256; i++)
    {
        c[i] = hist[i];
        c[i] /= n;
    }

    for (i = 1; i < 256; i++)
        c[i] += c[i - 1];

    int j = 0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            result[i][j] = c[d[i][j]] * 255;

    return result;
}
int **interpolation_knn(int **d, int n_ligne, int n_col, int ki, int kj){
    int **result = create_matrix(n_ligne*ki, n_col*kj);
    int i=0, j=0, vali=0,valj=0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            for (vali = i*ki; vali < ki*(i+1); vali++)
                for (valj = j*kj; valj < kj*(j+1); valj++)
                    result[vali][valj] = d[i][j];
    return result;
}
int **interpolation_bilineaire(int **d, int n_ligne, int n_col){
    int nl= n_ligne*2-1,nc= n_col*2-1;
    int **result = create_matrix(nl, nc);
    int i=0, j=0;
    for (i = 0; i < n_ligne; i++){
        for (j = 0; j < n_col; j++){
            result[2*i][2*j]=d[i][j];
            if (2*i+1 < nl)
            {
                result[2*i+1][2*j]=(d[i][j]+d[i+1][j])/2;
            }
            if (2*j+1 < nc)
            {
                result[2*i][2*j+1]=(d[i][j]+d[i][j+1])/2;
            }
            if (2*i+1 < nl && 2*j+1 < nc )
            {
                result[2*i+1][2*j+1]=(d[i][j]+d[i+1][j]+d[i][j+1]+d[i+1][j+1])/4;
            }
        }
    }
    return result;
}