#ifndef CONVOLUTION_H_INCLUDED
#define CONVOLUTION_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int ** filtre_gausien(unsigned int pas);
int ** read_filtre(char * path);


#endif // CONVOLUTION_H_INCLUDED