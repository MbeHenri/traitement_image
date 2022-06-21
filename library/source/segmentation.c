#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "../entete/segmentation.h"
#include "../entete/base.h"
#include "../entete/stack/stack.h"
#include "../entete/stack/couple.h"

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
            jw += dispersion_c[k] / nelem_c[k];
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
    int aux=0;
    int x_ = 0, y_ = 0;
    printf("%d-%d\n",x,y);
    for (a = 0; a < 3; a++)
    {
        for (b = 0; b < 3; b++)
        {
            x_ = x + a - 1; y_ = y + b - 1;
            if (x_ >= 0 && y_ >= 0 && y_ < n_ligne && x_ < n_col && x_ != x && y_ != y)
            {
                aux = abs(d[y][x] - d[y_][x_]);
                if (aux < e && marque[y_][x_] != 1)
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
        for (j = 0; j < n_col; j++)
            marque[i][j] = 255;
    /*
    germe_r(d, marque, n_ligne, n_col, x, y, e);
    */
    stack pile = new_stack();
    int xc=0,yc=0,a = 0, b = 0, x_, y_;
    push(pile, x,y);
    while (is_empty_stack(pile)==False)
    {
        pop(pile, &xc, &yc);
        marque[yc][xc] = 0;
        for (a = 0; a < 3; a++)
        {
            for (b = 0; b < 3; b++)
            {
                x_ = xc + a - 1; y_ = yc + b - 1;
                if (x_ >= 0 && y_ >= 0 && y_ < n_ligne && x_ < n_col && x_ != xc && y_ != yc)
                    if (abs(d[yc][xc] - d[y_][x_]) < e && marque[y_][x_] != 0)
                        push(pile,x_,y_);
            }
        }
    }
    free_stack(pile);
    return marque;
}
int **seuillage(int **d, int n_ligne, int n_col, double seuil)
{
    int *hist = histogram(d, n_ligne, n_col);
    int n1 = 0;int val1=0;
    int n2 = 0;int val2=2;
    int i=0,j=0;
    for (i = 0; i < 256; i++)
    {
        if(i < seuil){
            n1+=hist[i];
            val1+=hist[i]*i;
        }else{
            n2+=hist[i];
            val2+=hist[i]*i;
        }
    }
    if (n1==0)
        val1=0;
    else
        val1/=n1;
        
    if (n2==0)
        val2=255;
    else
        val2/=n2;
    for (i = 0; i < 256; i++)
        if (i < seuil)
            hist[i]=val1;
        else
            hist[i]=val2;
            
    int **result = create_matrix(n_ligne, n_col);
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            result[i][j] = hist[d[i][j]];
        
    return result;
}
int **seuillage_multiple(int **d, int n_ligne, int n_col, double* seuils, int n_seuils)
{
    int *hist = histogram(d, n_ligne, n_col);
    int* ns = malloc((1+n_seuils)*sizeof(int));
    int* vals = malloc((1+n_seuils)*sizeof(int));
    int i=0,j=0;
    for (i = 0; i <= n_seuils; i++)
    {
        ns[i]=0;vals[i]=0;
    }
    j=0;
    for (i = 0; i < 256; i++)
    {   
        if(j!=n_seuils && i >= seuils[j])
            j++;
         
        ns[j]+=hist[i];
        vals[j]+=hist[i]*i;
    }
    for (i = 0; i <= n_seuils; i++)
    {
        if(ns[i]==0)
            if (i==0)
                vals[i]=0;
            else
                vals[i]=seuils[i-1];
        else
            vals[i]/=ns[i];
    }
    j=0;
    for (i = 0; i < 256; i++){
        if(j!=n_seuils && i >= seuils[j])
            j++;
        hist[i]=vals[j];
    }
            
    int **result = create_matrix(n_ligne, n_col);
    for (i = 0; i < n_ligne; i++)
        for (j = 0; j < n_col; j++)
            result[i][j] = hist[d[i][j]];
        
    return result;
}
int **seuillage_auto_otsu(int **d, int n_ligne, int n_col)
{
    int *hist = histogram(d, n_ligne, n_col);
    double variance_intra_classe_min = __DBL_MAX__;
    int seuil = 0,T=0;
    const int nbs = n_ligne*n_col; 
    for ( T = 1; T < 255; T++)
    {
        double m1=0,m2=0,p1=0,p2=0,v1=0,v2=0;
        for (int i = 0; i < 256; i++)
            if (i<T)
                m1+=hist[i];
            else
                m2+=hist[i];
        p1 = m1/nbs;
        p2 = m2/nbs;
        m1/=T;
        m2/=(256-T);
        for (int i = 0; i < 256; i++)
            if (i<T)
                v1+=(hist[i]-m1)*(hist[i]-m1);
            else
                v2+=(hist[i]-m2)*(hist[i]-m2);
        v1/=T;
        v2/=(256-T);
        const double variance_intra_classe_courant = p1*v1 + p2*v2;
        if (variance_intra_classe_courant < variance_intra_classe_min)
        {
            variance_intra_classe_min = variance_intra_classe_courant;
            seuil = T;
        }
    }
    printf(" variance intra-classe minimale: %f\n", variance_intra_classe_min);
    printf(" seuil trouvé : %d\n", seuil);
    return seuillage(d, n_ligne, n_col, seuil);
}