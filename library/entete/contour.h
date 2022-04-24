#ifndef CONTOUR_H_INCLUDED
#define CONTOUR_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

int **transformer_hough(int **d, unsigned int n_ligne, unsigned int n_col, double *theta, double n_theta, double *beta, double n_beta);


int **gradient_prewitt(int **d, unsigned int n_ligne, unsigned int n_col);
int **gradient_sobel(int **d, unsigned int n_ligne, unsigned int n_col);
int **gradient_robert(int **d, unsigned int n_ligne, unsigned int n_col);
int **laplacien(int **d, unsigned int n_ligne, unsigned int n_col);

#endif // CONTOUR_H_INCLUDED