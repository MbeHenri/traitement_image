#ifndef CONVOLUTION_H_INCLUDED
#define CONVOLUTION_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct Filtre Filtre;
struct Filtre
{
    unsigned int pas;
    int ** data;
};
void free_Filtre();

int ** filtre_gausien(unsigned int pas);

int ** filtre_robert_x();
int ** filtre_robert_y();
int ** filtre_prewitt_x();
int ** filtre_prewitt_y();
int ** filtre_sobel_x();
int ** filtre_sobel_y();

int ** filtre_laplacien_1();
int ** filtre_laplacien_2();

Filtre* read_filtre(char * path);
double ** norm_filtre(int ** filtre, unsigned int pas);
int ** convoluer(int **d, unsigned int n_ligne, unsigned int n_col, int ** filtre, unsigned int pas);

#endif // CONVOLUTION_H_INCLUDED