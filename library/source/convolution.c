#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "base.h"

int **filtre_gausien(unsigned int pas)
{
    unsigned int n = 2 * pas + 1;
    int **result = create_matrix(n, n);

    return result;
}
int **read_filtre(char *path, unsigned int *n)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
    {
        exit(1);
    }
    unsigned int pas = 0, ;
    fscanf(f, "%d\n", &pas);
    *n = 2 * pas + 1;
    int **filtre = create_matrix(n, n);
    unsigned int i, j;
    for (i = 0; i < *n; i++)
        for (j = 0; j < *n; j++)
            fscanf(f, "%d", &filtre[i][j]);
    return filtre;
}