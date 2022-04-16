#ifndef INTERPOLATION_H_INCLUDED
#define INTERPOLATION_H_INCLUDED
#include "Image.h"

/*
    interpolation d'images (changement d'echelle)
*/
//pour les images a couleur de gris et binaire
int** interpolation_knn(int **d, unsigned int n_ligne, unsigned int n_col, int k);
int** interpolation_bilineaire(int **d, unsigned int n_ligne, unsigned int n_col);
int** interpolation_bicubique(int **d, unsigned int n_ligne, unsigned int n_col);

#endif // INTERPOLATION_H_INCLUDED