#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../entete/base.h"

int indice_val_proche(double *d, int len, double val)
{
    int ind = 0;
    while (d[ind] <= val && ind < len)
    {
        ind++;
    }
    ind--;
    if (ind < 0 || (ind == len - 1 && d[ind] != val))
    {
        return -1;
    }
    if (d[ind] == val)
    {
        return ind;
    }
    if (2 * val - d[ind + 1] - d[ind] <= 0)
    {
        return ind;
    }
    return ind + 1;
}

int **create_matrix(int n_ligne, int n_col)
{
    int **d = (int **)malloc(n_ligne * sizeof(int *));
    if (d == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels ]\n");
        exit(1);
    }
    int i = 00;
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
int **copie_matrix(int **d, int n_ligne, int n_col)
{
    int **r = create_matrix(n_ligne, n_col);
    int i, j;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            r[i][j] = d[i][j];
        }
    }
    return r;
}
double **create_matrix_d(int n_ligne, int n_col)
{
    double **d = (double **)malloc(n_ligne * sizeof(double *));
    if (d == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour les valeurs de pixels ]\n");
        exit(1);
    }
    int i = 0;
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
void free_matrix(int **d, int n_ligne)
{
    int i = 0;
    for (i = 0; i < n_ligne; i++)
        free(d[i]);
    free(d);
}
void free_matrix_d(double **d, int n_ligne)
{
    int i = 0;
    for (i = 0; i < n_ligne; i++)
        free(d[i]);
    free(d);
}

int *histogram(int **d, int n_ligne, int n_col)
{
    int *hist = (int *)malloc(255 * sizeof(int));
    if (hist == NULL)
    {
        printf("[ impossible d'allouer de la memoire pour l'histogramme ]\n");
        exit(1);
    }
    int i = 0, j = 0;
    for (i = 0; i < 256; i++)
        hist[i] = 0;

    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            hist[d[i][j]]++;

    return hist;
}

double luminance(int **d, int n_ligne, int n_col)
{
    int sum = 0;
    int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            sum += d[i][j];

    return sum / (n_col * n_ligne);
}

int max_(int **d, int n_ligne, int n_col)
{
    int m = 0;
    int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            if (d[i][j] > m)
                m = d[i][j];
    return m;
}
int min_(int **d, int n_ligne, int n_col)
{
    int m = 255;
    int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            if (d[i][j] < m)
                m = d[i][j];
    return m;
}
double contraste_ecart_type(int **d, int n_ligne, int n_col)
{
    int i = 0, j = 0;
    double moy = luminance(d, n_ligne, n_col);
    double result = 0;
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            result += pow((double)(d[i][j]) - moy, 2.0);

    return sqrt(result / (n_col * n_ligne));
}

double contraste_min_max(int **d, int n_ligne, int n_col)
{
    int min = min_(d, n_ligne, n_col), max = max_(d, n_ligne, n_col);
    return ((double)(max - min)) / (max + min);
}

int **plus_(int **d1, int **d2, int n_ligne, int n_col)
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

int **fois_(int **d_, int n_ligne, int n_col, double ratio)
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

int **moins_(int **d1, int **d2, int n_ligne, int n_col)
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
int **et_(int **d1, int **d2, int n_ligne, int n_col, int a)
{
    int **d = create_matrix(n_ligne, n_col);
    int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_ligne; j++)
        {
            d[i][j] = a;
            if (d1[i][j] == 0)
                d[i][j] = d2[i][j];
        }
    }
    return d;
}
int **ou_(int **d1, int **d2, int n_ligne, int n_col, int a)
{
    int **d = create_matrix(n_ligne, n_col);
    int i = 0, j = 0;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_ligne; j++)
        {
            d[i][j] = a;
            if (d1[i][j] == 1)
                d[i][j] = d2[i][j];
        }
    }
    return d;
}

Vector *profil_intensite_(int **d, int x1, int y1, int x2, int y2)
{
    int x, y, max = 0, min = 0;
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
int **replace_line_(int **d, int n_ligne, int n_col, int x1, int y1, int x2, int y2, int val_replace)
{
    int **r = copie_matrix(d, n_ligne, n_col);
    int x, y, max = 0, min = 0;
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
            r[((y2 - y1) / (x2 - x1)) * (x - x1) + y1][x] = val_replace;
    }
    return r;
}

int **replace_circle_(int **d, int n_ligne, int n_col, int xr, int yr, double rayon, int val_replace)
{
    int **r = create_matrix(n_ligne, n_col);
    int x, y, a, b = rayon * rayon;
    for (y = 0; y < n_ligne; y++)
    {
        for (x = 0; x < n_col; x++)
        {
            a = (x - xr) * (x - xr) + (y - yr) * (y - yr);
            if (a == b)
            {
                r[y][x] = val_replace;
            }
            else
            {
                r[y][x] = d[y][x];
            }
        }
    }
    return r;
}
int **replace_disque_(int **d, int n_ligne, int n_col, int xr, int yr, double rayon, int val_replace)
{
    int **r = create_matrix(n_ligne, n_col);
    int x, y, a, b = rayon * rayon;
    for (y = 0; y < n_ligne; y++)
    {
        for (x = 0; x < n_col; x++)
        {
            a = (x - xr) * (x - xr) + (y - yr) * (y - yr);
            if (a < b)
            {
                r[y][x] = val_replace;
            }
            else
            {
                r[y][x] = d[y][x];
            }
        }
    }
    return r;
}

int **replace_rectangle_(int **d, int n_ligne, int n_col, int xr, int yr, double longueur, double largeur, int val_replace)
{
    int **r = create_matrix(n_ligne, n_col);
    int x, y;
    for (y = 0; y < n_ligne; y++)
    {
        for (x = 0; x < n_col; x++)
        {
            int x_ = x - xr, y_ = y - yr;
            if (x_ >= 0 && x_ <= longueur && y_ >= 0 && y_ <= largeur)
            {
                r[y][x] = val_replace;
            }
            else
            {
                r[y][x] = d[y][x];
            }
        }
    }
    return r;
}

void replace_on_line_(int **d, int x1, int y1, int x2, int y2, int val_replace)
{
    int x, y, max = 0, min = 0;
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
            d[y][x2] = val_replace;
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
}
void replace_on_disque_(int **d, int n_ligne, int n_col, int xr, int yr, double rayon, int val_in, int val_e)
{
    int x, y, a, b = rayon * rayon;
    for (y = 0; y < n_ligne; y++)
    {
        for (x = 0; x < n_col; x++)
        {
            a = (x - xr) * (x - xr) + (y - yr) * (y - yr);
            if (a < b)
            {
                d[y][x] = val_in;
            }
            else if (a == b)
            {
                d[y][x] = val_e;
            }
        }
    }
}
void replace_on_rectangle_(int **d, int n_ligne, int n_col, int xr, int yr, double longueur, double largeur, int val_in, int val_e)
{

    int x, y;
    for (y = 0; y < n_ligne; y++)
    {
        for (x = 0; x < n_col; x++)
        {
            int x_ = x - xr, y_ = y - yr;
            if (x_ >= 0 && x_ <= longueur && y_ >= 0 && y_ <= largeur)
            {
                d[y][x] = val_in;
            }
        }
    }
}

int **binarisation(int **d, int n_ligne, int n_col, double seuil)
{
    int **r = create_matrix(n_ligne, n_col);
    int i, j;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            if (d[i][j] > seuil)
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

int **changer_plage(int **d, int n_ligne, int n_col, int a1, int a2, int min, int max)
{
    int **r = create_matrix(n_ligne, n_col);
    int i, j;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            if (d[i][j] <= a2 && d[i][j] >= a1)
            {
                r[i][j] = (max - min) * (d[i][j] - a1) / (a2 - a1) + min;
            }
            else
            {
                r[i][j] = 0;
            }
        }
    }
    return r;
}

int **difference(int **d, int n_ligne, int n_col, int a)
{
    int **r = create_matrix(n_ligne, n_col);

    int i, j;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            r[i][j] = abs(a - d[i][j]);
        }
    }
    return r;
}
void sortTab(int *d, int n)
{
    tri_bulle_int(d, n);
}
// TRI FUSION
void tri_bulle_int(int *tableau, int taille)
{
    int i = 0, j = 0, k = taille;
    int aux;
    for (i = 0; i < taille; i++)
    {
        for (j = 0; j < k - 1; j++)
        {
            if (tableau[j] > tableau[j + 1])
            {
                aux = tableau[j];
                tableau[j] = tableau[j + 1];
                tableau[j + 1] = aux;
            }
        }
    }
}

int **selection_k_max(int **d, int n_ligne, int n_col, int k)
{
    int **max = create_matrix(k, 2);
    int i, j, ind, s;
    for (i = 0; i < k; i++)
    {
        // indice ligne
        max[i][0] = 0;
        // indice colonne
        max[i][1] = 0;
    }
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
        {
            ind = 0;
            while (d[i][j] <= d[max[ind][0]][max[ind][1]] && ind < k)
            {
                k++;
            }
            if (ind < k)
            {
                s = ind + 1;
                while (s < k)
                {
                    max[s][0] = max[s - 1][0];
                    max[s][1] = max[s - 1][1];
                    s++;
                }
                max[ind][0] = i;
                max[ind][1] = j;
            }
        }
    }
    return max;
}

int **matrice_hist(int npixels, int *hist, int len_hist, int ecart_x, int esp_haut, int esp_gauche, int esp_bas, int esp_droite, int longeur, int val_rep, int val_bord, int val_in)
{
    int col = esp_gauche + esp_droite + (len_hist+2)*ecart_x , lig = esp_haut +esp_bas+ longeur;
    int ** r = create_matrix(lig, col);
    int i, j;
    for (i = 0; i < lig; i++)
        for (j = 0; j < col; j++)
            r[i][j] = 255;
            
    //dessin de la ligne horizontale
    int x1 = esp_gauche - 1, y1= esp_haut -1, x2= esp_gauche - 1, y2=esp_haut + longeur -1;
    replace_on_line_(r,x1,y1,x2,y2,val_rep);
    
    //dessin de la ligne verticale
    x1 += (len_hist+2)*ecart_x; y1+=longeur;
    replace_on_line_(r,x1,y1,x2,y2,val_rep);
    
    //dessin des tirets sur la ligne horizontale
    x1 = esp_gauche - 5; x2 = esp_gauche - 1;
    for (i = 0; i <= 4; i++)
    {
        y1 = esp_haut + i*longeur/4 -1;
        y2 = y1;
        replace_on_line_(r,x1,y1,x2,y2,val_rep);
    }
    
    //dessin des tirets sur la ligne verticale
    y1= longeur + esp_haut - 1; y2 =y1 + 3;
    for (i = 0; i <= len_hist; i++)
    {
        x1 = esp_gauche + i*ecart_x - 1;
        x2 = x1;
        replace_on_line_(r,x1,y1,x2,y2,val_rep);
    }
    
    //tracez des rectangles
    y2= longeur + esp_haut - 4;
    int taille;
    for (i = 0; i < len_hist; i++)
    {
        taille = longeur *  hist[i] / npixels;
        x1 = esp_gauche + (1+i)*ecart_x -1;
        y1 = y2+3 - taille;
        replace_on_rectangle_(r,lig,col,x1,y1,ecart_x,taille, val_in, val_bord);
    }
    return r;
}