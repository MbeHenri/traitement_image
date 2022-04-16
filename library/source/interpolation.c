#include <stdio.h>
#include <stdlib.h>

#include "../entete/base.h"

int** interpolation_knn(int **d, unsigned int n_ligne, unsigned int n_col, int k);
int** interpolation_bilineaire(int **d, unsigned int n_ligne, unsigned int n_col);
int** interpolation_bicubique(int **d, unsigned int n_ligne, unsigned int n_col);
