#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "library/entete/base.h"

int main(int argc, char const *argv[])
{

    double min = atof(argv[1]), max = atof(argv[2]);
    double ecart = atof(argv[3]);
    Vector_d* d = echantillonage(min, max, ecart);
    
    if (d->n == 0)
    {
        printf("Rien est possible\n");
        exit(1);
    }
    unsigned int i = 0;
    for ( i = 0; i < d->n; i++)
    {
        printf("%f ", d->data[i]);
    }
    printf("\n%d\n", d->n);
    free_vector_d(d);
    return 0;
}