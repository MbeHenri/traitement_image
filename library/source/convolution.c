#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "base.h"

int **filtre_gausien(unsigned int pas, double ecart_type)
{
    unsigned int n = 2 * pas + 1;
    int **result = create_matrix(n, n);
    unsigned int u,v;
    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
            result[u][v]=exp(-(u*u +v*v)/(2*ecart_type*ecart_type));
    return result;
}
int **filtre_moyenneur(unsigned int pas)
{
    unsigned int n = 2 * pas + 1;
    int **result = create_matrix(n, n);
    unsigned int u,v;
    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
            result[u][v]=1;
    return result;
}
int **read_filtre(char *path, unsigned int *pas)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
    {
        exit(1);
    }
    fscanf(f, "%d\n", pas);
    unsigned int n = 2 * (*pas) + 1;
    int **filtre = create_matrix(n, n);
    unsigned int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fscanf(f, "%d", &filtre[i][j]);
    return filtre;
}
double **norm_filtre(int **filtre, unsigned int pas)
{
    double **result = create_matrix_d(n, n);
    unsigned int i, j, n = 2 * pas + 1;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            result[i][j] = filtre[i][j] / (n * n);
    return result;
}

int **convoluer(int **d, unsigned int n_ligne, unsigned int n_col, double **filtre, unsigned int pas)
{
    int **result = create_matrix(n_ligne, n_col);
    int n = 2 * pas;
    int d_[n_ligne + n][n_col + n];
    unsigned int i, j, u, v;
    for (i = 0; i < n_ligne + n; i++)
    {
        for (j = 0; j < n_col + n; j++)
        {
            if (i < n || i > n_ligne)
            {
                d_[i][j] = 0;
            }
            else if (j < n || j > n_col)
            {
                d_[i][j] = 0;
            }
            else
            {
                d_[i][j] = d[i][j];
            }
        }
    }
    for (i = pas; i < n_ligne + pas; i++)
    {
        for (j = pas; j < n_col + pas; j++)
        {
            result[i - pas][j - pas] = 0;
            for (u = 0; u < 1 + n; u++)
                for (v = 0; v < 1 + n; v++)
                    result[i - pas][j - pas] += d_[i - pas + u][j - pas + v] * filtre[u][v];

            if (result[i - pas][j - pas] > 255)
            {
                result[i - pas][j - pas] = 255;
            }
            else if (result[i - pas][j - pas] < 0)
            {
                result[i - pas][j - pas] = 0;
            }
        }
    }
    return result;
}