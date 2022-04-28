#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../entete/base.h"
#include "../entete/Vector.h"

Vector_d *echantillonage(double min, double max, double ecart)
{
    unsigned int n = 0;
    // on recherche le nombre le nombre d'ecart possible partant de la valeur minimale
    while (min + ecart * n > max || min + ecart * (n + 1) >= max)
    {
        n++;
    }
    Vector_d *result = create_vector_d(n + 1);
    unsigned int i = 0;
    // on construit un vecteur constituant les valeurs suuccessives d'ecart
    for (i = 0; i < (n + 1); i++)
    {
        result->data[i] = min + ecart * i;
    }
    return result;
}

int **create_matrix(unsigned int n_ligne, unsigned int n_col)
{
    int **d = (int **)malloc(n_ligne * sizeof(int *));
    if (d == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels ]\n");
        exit(1);
    }
    int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
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
int ** copie_matrix(int **d, unsigned int n_ligne, unsigned int n_col)
{
    int **r = create_matrix(n_ligne, n_col);
    unsigned int i, j;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            r[i][j] = d[i][j];
        }
    }
    return r;
}
double **create_matrix_d(unsigned int n_ligne, unsigned int n_col)
{
    double **d = (double **)malloc(n_ligne * sizeof(double *));
    if (d == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels ]\n");
        exit(1);
    }
    int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
    {
        d[i] = (double *)malloc(n_col * sizeof(double));
        if (d[i] == NULL)
        {
            printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels ]\n");
            exit(1);
        }
    }
    return d;
}
void free_matrix(int **d, unsigned int n_ligne)
{
    int i = 0;
    for (i = 0; i < n_ligne; i++)
        free(d[i]);
    free(d);
}
void free_matrix_d(double **d, unsigned int n_ligne)
{
    unsigned int i = 0;
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

    return sum / (n_col * n_ligne);
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

int **plus_(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col)
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

int **fois_(int **d_, unsigned int n_ligne, unsigned int n_col, double ratio)
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

int **moins_(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col)
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
int **et_(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col, int a)
{
    int **d = create_matrix(n_ligne, n_col);
    int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_ligne; j++)
        {
            d[i][j] = a;
            if( d1[i][j] == 0 )
                d[i][j] = d2[i][j];
        }
    }
    return d;
}
int **ou_(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col, int a)
{
    int **d = create_matrix(n_ligne, n_col);
    int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_ligne; j++)
        {
            d[i][j] = a;
            if( d1[i][j] == 1 )
                d[i][j] = d2[i][j];
        }
    }
    return d;
}

Vector *profil_intensite_(int **d, unsigned int n_ligne, unsigned int n_col, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
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
int **replace_line_(int **d, unsigned int n_ligne, unsigned int n_col, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, int val_replace)
{
    int **r = copie_matrix(d, n_ligne, n_col);
    unsigned int x, y, v, max = 0, min = 0;
    if (x1 == x2)
    {
        max = y1;
        min = y2;
        if (max < y2)
        {
            min = y1;
            max = y2;
        }
        for (y = min; y <= max; y++)
            r[y][x2] = val_replace;
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
        for (x = min; x <= max; x++)
            d[((y2 - y1) / (x2 - x1)) * (x - x1) + y1][x] = val_replace;
    }
    return r;
}

int **replace_circle_(int **d, unsigned int n_ligne, unsigned int n_col, unsigned int xr, unsigned int yr, double rayon , int val_replace)
{
    int **r = create_matrix(n_ligne, n_col);
    unsigned int x, y;
    for ( y = 0; y < n_ligne; y++)
    {
        for ( x = 0; x < n_col; x++)
        {
            if (pow(x-xr,2.0) + pow(y-yr,2.0) == pow(rayon,2.0))
            {
                r[y][x] = val_replace;
            }else{
                r[y][x] = d[y][x];
            }
        }   
    }
    return r;
}
int **replace_disque_(int **d, unsigned int n_ligne, unsigned int n_col, unsigned int xr, unsigned int yr, double rayon , int val_replace)
{
    int **r = create_matrix(n_ligne, n_col);
    unsigned int x, y, a, b=rayon*rayon;
    for ( y = 0; y < n_ligne; y++)
    {
        for ( x = 0; x < n_col; x++)
        {
            a = (x- xr)*(x- xr) + (y-yr)*(y-yr);
            if( a<b ){
                r[y][x] = val_replace;
            }else{
                r[y][x] = d[y][x];
            }
        }   
    }
    return r;
}

int **binarisation(int **d, unsigned int n_ligne, unsigned int n_col, double seuil)
{
    int **r = create_matrix(n_ligne, n_col);
    unsigned int i, j;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            if (d[i][j] < seuil)
            {
                r[i][j] = 0;
            }
            else
            {
                r[i][j] = 1;
            }
        }
    }
    return r;
}

int **changer_plage(int **d, unsigned int n_ligne, unsigned int n_col, int a1, int a2, int min, int max)
{
    int **r = create_matrix(n_ligne, n_col);
    unsigned int i, j;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            if (d[i][j] <= a2 && d[i][j] >= a1)
                r[i][j] = (max - min) * (d[i][j] - a1) / (a2 - a1) + min;
    return r;
}

int **difference(int **d, unsigned int n_ligne, unsigned int n_col, int a)
{
    int **r = create_matrix(n_ligne, n_col);

    unsigned int i, j;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            r[i][j] = abs(a - d[i][j]);
        }
    }
    return r;
}