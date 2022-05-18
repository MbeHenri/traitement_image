#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "../entete/segmentation.h"
#include "../entete/base.h"

int **kmeans(int **d, int n_ligne, int n_col, int K, int min, int max, double e1, double e2)
{
    int *nelem_c = malloc(K * sizeof(int));
    double *dispersion_c = malloc(K * sizeof(double));
    double *centre_c = malloc(K * sizeof(double));
    int **tab_c = create_matrix(n_ligne, n_col);
    double jw = 0;
    double dn = 0;

    double *centre_aux_c = malloc(K * sizeof(double));
    int i, j, k, kmin, niter = 0;
    double vmin, aux;

    srand(time(NULL));
    for (k = 0; k < K; k++)
    {
        jw = rand() / (RAND_MAX + 1.0);
        centre_c[k] = (max - min) * jw + min;
    }

    do
    {
        // mises a zeros des dispersions et des nombres d'elements par clusters
        for (k = 0; k < K; k++)
        {
            nelem_c[k] = 0;
            dispersion_c[k] = 0;
            centre_aux_c[k] = 0;
        }
        // initialisation des elements de clusters et de leurs dispersions
        for (i = 0; i < n_ligne; i++)
        {
            for (j = 0; j < n_col; j++)
            {
                kmin = 0;
                vmin = fabs(d[i][j] - centre_c[kmin]);
                for (k = 1; k < K; k++)
                {
                    aux = fabs(d[i][j] - centre_c[k]);
                    if (vmin > aux)
                    {
                        kmin = k;
                        vmin = aux;
                    }
                }
                tab_c[i][j] = kmin;
                nelem_c[kmin]++;
                dispersion_c[kmin] += vmin * vmin;
                centre_aux_c[kmin] += d[i][j];
            }
        }
        // calcul de la dispersion totale, des nouveaux centres de clusters et la variation de ces dernieres nomme dn
        jw = 0;
        dn = 0;
        for (k = 0; k < K; k++)
        {
            jw += sqrt(dispersion_c[k] / nelem_c[k]);
            centre_aux_c[k] /= nelem_c[k];
            dn += fabs(centre_c[k] - centre_aux_c[k]);
            centre_c[k] = centre_aux_c[k];
        }
        niter++;
    } while (dn > e1 && jw > e2);
    printf("nombres iterations : %d \ndistance de convergence des centres finales : %f\ninertie intraclasse finale : %f\n", niter, dn, jw);
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            tab_c[i][j] = centre_c[tab_c[i][j]];
    return tab_c;
}

void germe_r(int **d, int **marque, const int n_ligne, const int n_col, int x, int y, const double e)
{
    marque[y][x] = 1;
    int a = 0, b = 0;
    for (a = 0; a < 3; a++)
    {
        for (b = 0; b < 3; b++)
        {
            int x_ = x + a - 1, y_ = y + b - 1;
            if (x_ >= 0 && y_ >= 0 && y_ < n_ligne && x_ < n_col && x_ != x && y_ != y)
            {
                double aux = abs(d[y][x] - d[y_][x_]);
                if (aux < e && marque[y_][x_] == 0)
                {
                    germe_r(d, marque, n_ligne, n_col, x_, y_, e);
                }
            }
        }
    }
}

int **germe(int **d, int n_ligne, int n_col, int x, int y, const double e)
{
    int **marque = create_matrix(n_ligne, n_col);
    int i, j;
    for (i = 0; i < n_ligne; i++)
    {
        for (j = 0; j < n_col; j++)
            marque[i][j] = 0;
    }
    germe_r(d, marque, n_ligne, n_col, x, y, e);
    return marque;
}
