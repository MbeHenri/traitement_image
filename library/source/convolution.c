#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../entete/base.h"
#include "../entete/convolution.h"

int **filtre_gausien(int pas, double ecart_type)
{
    int n = 2 * pas + 1;
    int **result = create_matrix(n, n);
    int y, x;
    for (y = 0; y < n; y++)
        for (x = 0; x < n; x++)
            result[y][x] = exp(-(y * y + x * x) / (2 * ecart_type * ecart_type));
    return result;
}
int **filtre_moyenneur(int pas)
{
    int n = 2 * pas + 1;
    int **result = create_matrix(n, n);
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            result[i][j] = 1;
    return result;
}

Filtre *read_filtre(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        return NULL;
    }

    Filtre *result = malloc(sizeof(Filtre));
    fscanf(f, "%d", &result->pas);
    int n = 2 * result->pas + 1;
    int i, j;
    result->data = create_matrix(n, n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fscanf(f, "%d", &result->data[i][j]);
    return result;
}
void free_Filtre(Filtre *filtre)
{
    free_matrix(filtre->data, 2 * filtre->pas + 1);
    free(filtre);
}
double **norm_filtre(int **filtre, int pas)
{
    int i, j, n = 2 * pas + 1;
    double **result = create_matrix_d(n, n);
    int sum = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            sum += filtre[i][j];
            result[i][j] = filtre[i][j];
        }
    }
    if (sum == 0)
    {
        return result;
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            result[i][j] = result[i][j] / sum;
    return result;
}

int **convoluer(int **d, int n_ligne, int n_col, double **filtre, int pas)
{
    int **result = create_matrix(n_ligne, n_col);
    int n = 2 * pas;
    int **d_ = create_matrix(n_ligne + n, n_col + n);
    int i, j, u, v;

    for (i = 0; i < n_ligne + n; i++)
    {
        for (j = 0; j < n_col + n; j++)
        {
            if (i < pas || i >= n_ligne)
            {
                d_[i][j] = 0;
            }
            else if (j < pas || j >= n_col)
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
            for (u = 0; u <= n; u++)
                for (v = 0; v <= n; v++)
                    result[i - pas][j - pas] += d_[i + u - pas][j + v - pas] * filtre[u][v];

            if (result[i - pas][j - pas] > 255)
                result[i - pas][j - pas] = 255;
            if (result[i - pas][j - pas] < 0)
                result[i - pas][j - pas] = 0;
        }
    }
    free_matrix(d_, n_ligne + n);
    return result;
}

int **convoluerMedian(int **d, int n_ligne, int n_col, int pas)
{
    int **result = create_matrix(n_ligne, n_col);

    int n = (2 * pas + 1) * (2 * pas + 1);
    int *vect = malloc(n * sizeof(int));
    int taille = 0;
    int i, j;

    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            // recherche des voisins
            taille = 0;
            const int ymax = i + pas, xmax = j + pas;
            int y, x;
            for (y = i - pas; y <= ymax; y++)
            {
                for (x = j - pas; x <= xmax; x++)
                {
                    if (x >= 0 && x < n_col && y >= 0 && y < n_ligne)
                    {
                        vect[taille] = d[y][x];
                        taille++;
                    }
                }
            }
            sortTab(vect, taille);
            result[i][j] = vect[taille / 2];
            if (taille % 2 == 0)
            {
                result[i][j] = vect[taille / 2 - 1];
            }
        }
    }
    free(vect);
    return result;
}