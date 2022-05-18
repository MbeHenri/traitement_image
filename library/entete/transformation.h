#ifndef AMELIORATION_H_INCLUDED
#define AMELIORATION_H_INCLUDED

/*
    Transformation lineaire et non lineaire
*/
int **transform_linear(int **d, int n_ligne, int n_col);
int **transform_linear_satur(int **d, int n_ligne, int n_col, int c_min, int c_max);
int **transform_linear_morceau(int **d, int n_ligne, int n_col, int *s, int *v, int len);

int **transform_no_linear(int **d, int n_ligne, int n_col);

/*
    egaliseur d'histogramme
*/
int **egalizer_hist(int **d, int n_ligne, int n_col);

/*
    interpolation d'images (changement d'echelle)
*/
int **interpolation_knn(int **d, int n_ligne, int n_col, int k);
int **interpolation_bilineaire(int **d, int n_ligne, int n_col);
int **interpolation_bicubique(int **d, int n_ligne, int n_col);

#endif // AMELIORATION_H_INCLUDED