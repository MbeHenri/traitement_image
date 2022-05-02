#ifndef AMELIORATION_H_INCLUDED
#define AMELIORATION_H_INCLUDED

/*
    Transformation lineaire 
*/
int **transform_linear(int **d, unsigned int n_ligne, unsigned int n_col);
int ** transform_linear_satur(int **d, unsigned int n_ligne, unsigned int n_col, int c_min, int c_max);
int ** transform_linear_morceau(int **d, unsigned int n_ligne, unsigned int n_col);
int ** transform_not_linear(int **d, unsigned int n_ligne, unsigned int n_col);

/*
    egaliseur d'histogramme
*/
int ** egalizer_hist(int **d, unsigned int n_ligne, unsigned int n_col);
int ** egalizer_hist_local(int **d, unsigned int n_ligne, unsigned int n_col, int pasVoisin);

/*
    interpolation d'images (changement d'echelle)
*/
int** interpolation_knn(int **d, unsigned int n_ligne, unsigned int n_col, int k);
int** interpolation_bilineaire(int **d, unsigned int n_ligne, unsigned int n_col);
int** interpolation_bicubique(int **d, unsigned int n_ligne, unsigned int n_col);

#endif // AMELIORATION_H_INCLUDED