#ifndef AMELIORATION_H_INCLUDED
#define AMELIORATION_H_INCLUDED
#include "base.h"

/*
    Amelioration d'images
*/
int **transform_linear(int **d, unsigned int n_ligne, unsigned int n_col);
int ** transform_linear_satur(int **d, unsigned int n_ligne, unsigned int n_col, int c_min, int c_max);
int ** transform_linear_morceau(int **d, unsigned int n_ligne, unsigned int n_col);
int ** transform_not_linear(int **d, unsigned int n_ligne, unsigned int n_col);
int ** egalizer_hist(int **d, unsigned int n_ligne, unsigned int n_col, char type);
int ** egalizer_hist_local(int **d, unsigned int n_ligne, unsigned int n_col, int pasVoisin);


#endif // AMELIORATION_H_INCLUDED