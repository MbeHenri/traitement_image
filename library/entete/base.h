#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"

int **create_matrix(unsigned int n_ligne, unsigned int n_col);
double **create_matrix_d(unsigned int n_ligne, unsigned int n_col);
void free_matrix(int **d, unsigned int n_ligne, unsigned int n_col);


// prototype de fonction de base
int *histogram(int **d, unsigned int n_ligne, unsigned int n_col);

double luminance(int **d, unsigned int n_ligne, unsigned int n_col);
double contraste_ecart_type(int **d, unsigned int n_ligne, unsigned int n_col);
double contraste_min_max(int **d, unsigned int n_ligne, unsigned int n_col);
unsigned int max_(int **d, unsigned int n_ligne, unsigned int n_col);
unsigned int min_(int **d, unsigned int n_ligne, unsigned int n_col);

int **plus(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col);
int **fois(int ** d_, unsigned int n_ligne, unsigned int n_col1, double ratio);
int **moins(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col);

Vector *profil_intensite(int **d, unsigned int n_ligne, unsigned int n_col, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
#endif // BASE_H_INCLUDED