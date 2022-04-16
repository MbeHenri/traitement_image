#ifndef CONVOLUTION_H_INCLUDED
#define CONVOLUTION_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int ** filtre_gausien(unsigned int pas);
int ** read_filtre(char * path);
double ** norm_filtre(int ** filtre, unsigned int pas);
int ** convoluer(int **d, unsigned int n_ligne, unsigned int n_col, int ** filtre, unsigned int pas);

#endif // CONVOLUTION_H_INCLUDED