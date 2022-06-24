#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../entete/base.h"
#include "../entete/change_domain.h"

int **transformer_hough(int **d, int n_ligne, int n_col, double *beta, int len_beta, double *theta, int len_theta, int color)
{
    int **result = create_matrix(len_beta, len_theta);
    int i, j, t;

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
                    const double aux = j * cos(PI * theta[t] / 180) + i * sin(PI * theta[t] / 180);
                    const int ind = indice_val_proche(beta, len_beta, aux);
                    if (ind > 0)
                        result[ind][t]++;
                }
            }
        }
    }
    return result;
}

Complex *transform_fourier_dim1(Complex *w, int n)
{
    Complex *wr = NULL;
    if (n == 1)
    {
        wr = new_tab_complex(1);
        copie_complex(w[0], wr[0]);
    }
    else
    {
        Complex *w_pair = new_tab_complex(n / 2);
        Complex *w_impair = new_tab_complex(n / 2);
        int i = 0;
        for (i = 0; i < n / 2; i++)
        {
            copie_complex(w[2 * i], w_pair[i]);
            copie_complex(w[2 * i + 1], w_impair[i]);
        }
        Complex *w_pair_p = transform_fourier_dim1(w_pair, n / 2);
        free_tab_complex(w_pair, n / 2);
        Complex *w_impair_p = transform_fourier_dim1(w_impair, n / 2);
        free_tab_complex(w_impair, n / 2);

        wr = new_tab_complex(n);
        for (i = 0; i < n / 2; i++)
        {
            wr[i]->rez = cos((2 * M_PI * (i+1)) / n);
            wr[i]->img = sin((2 * M_PI * (i+1)) / n);
            fois_complex(wr[i], w_impair_p[i], wr[n / 2 + i]);
            plus_complex(w_pair_p[i], wr[n / 2 + i], wr[i]);
            moins_complex(w_pair_p[i], wr[n / 2 + i], wr[n / 2 + i]);
        }
        free_tab_complex(w_impair_p, n / 2);
        free_tab_complex(w_pair_p, n / 2);
    }
    return wr;
}

Complex **transform_fourier_dim2(Complex **d, int n_ligne, int n_col)
{
    Complex** resultat = new_matrix_complex(n_ligne, n_col);
    Complex* s = NULL;
    int i = 0,j=0;
    for (i = 0; i < n_ligne; i++)
    {
        s = new_tab_complex(n_col);
        for ( j = 0; j < n_col; j++)
            copie_complex(d[i][j], s[j]);
        
        Complex* s_p = transform_fourier_dim1(s,n_col);
        free_tab_complex(s, n_col);
        
        for ( j = 0; j < n_col; j++)
            copie_complex(s_p[j],resultat[i][j]);
            
        free_tab_complex(s_p, n_col);
    }
    for (j = 0; j < n_col; j++)
    {
        s = new_tab_complex(n_ligne);
        for ( i = 0; i < n_ligne; i++)
            copie_complex(resultat[i][j], s[i]);
        
        Complex* s_p = transform_fourier_dim1(s,n_ligne);
        free_tab_complex(s, n_ligne);
        
        for ( i = 0; i < n_col; i++)
            copie_complex(s_p[i],resultat[i][j]);
            
        free_tab_complex(s_p, n_ligne);
    }
    return resultat;
}