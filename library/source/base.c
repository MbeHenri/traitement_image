#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../entete/base.h"

int **create_matrix(unsigned int n_ligne, unsigned int n_col)
{
    int **d = (int **)malloc(n_ligne * sizeof(int *));
    if (d == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels ]\n");
        exit(1);
    }
    int i = 0, j = 0;
    for (i = 0; i < img->nLigne; i++)
    {
        d[i] = (int *)malloc(n_col * sizeof(int));
        if (d[i] == NULL)
        {
            printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels ]\n");
            exit(1);
        }
    }
    return d;
}

void free_matrix(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int i = 0;
    for (i = 0; i < n_ligne; i++)
        free(d[i]);
    free(d);
}

int *histogram(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int *hist = (int *)malloc(255 * sizeof(int));
    if (hist == NULL)
    {
        printf("[ impossible d'allouer de la memoire pour l'histogramme ]\n");
        exit(1);
    }
    unsigned int i = 0, j = 0;
    for (i = 0; i < 256; i++)
        hist[i] = 0;

    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            hist[d[i][j]]++;

    return hist;
}

double luminance(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int sum = 0;
    unsigned int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            sum += d[i][j];

    return sum / (img->nColonne * img->nLigne);
}

int max_(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int m = 0, i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            if (d[i][j] > m)
                m = d[i][j];
    return m;
}
int min_(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int m = 255, i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            if (d[i][j] < m)
                m = d[i][j];
    return m;
}
double contraste_ecart_type(int **d, unsigned int n_ligne, unsigned int n_col)
{
    unsigned int i = 0, j = 0;
    double moy = luminance(d, n_ligne, n_col);
    double result = 0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            result += pow((double)(d[i][j]) - moy, 2.0);
            
    return sqrt(result / (n_col * n_ligne));
}
double contraste_min_max(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int min = min_(d, n_ligne, n_col), max = max_(d, n_ligne, n_col);
    return ((double)(max - min)) / (max + min);
}

int **plus(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col)
{
    int **d = create_matrix(n_ligne, n_col);
    int i, j;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            d[i][j] = d1[i][j] + d2[i][j];
            if (d[i][j] >= 255)
                d[i][j] = 255;
        }
    }
    return d;
}

int **fois(int **d_, unsigned int n_ligne, unsigned int n_col, double ratio)
{
    int **d = create_matrix(n_ligne, n_col);
    int i, j;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            d[i][j] = ratio * d_[i][j];
            if (d[i][j] > 255)
                d[i][j] = 255;
            if (d[i][j] < 0)
                d[i][j] = 0;
        }
    }
    return d;
}

int **moins(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col)
{
    int **d = create_matrix(n_ligne, n_col);
    int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_ligne; j++)
        {
            d[i][j] = d1[i][j] - d2[i][j];
            if (d[i][j] < 0)
                d[i][j] = 0;
        }
    }
    return d;
}

Vector *profil_intensite(int **d, unsigned int n_ligne, unsigned int n_col, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    unsigned int x, y, v, max = 0, min = 0;
    Vector *result = NULL;
    if (x1 == x2)
    {
        max = y1;
        min = y2;
        if (max < y2)
        {
            min = y1;
            max = y2;
        }
        result = create_vector(max - min + 1);
        for (y = min; y <= max; y++)
            result->data[y - min] = d[y][x2];
    }
    else
    {
        max = x1;
        min = x2;
        if (max < x2)
        {
            min = x1;
            max = x2;
        }
        result = create_vector(max - min + 1);
        for (x = min; x <= max; x++)
            result->data[x - min] = d[((y2 - y1) / (x2 - x1)) * (x - x1) + y1][x];
    }
    return result;
}