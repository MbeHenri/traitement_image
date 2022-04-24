#include <stdio.h>
#include <stdlib.h>

#include "../entete/Vector.h"

Vector *create_vector(unsigned int len)
{
    Vector *result = (Vector *)malloc(sizeof(Vector));
    if (result == NULL)
    {
        printf(" [ un probleme d'allocation de memoire est survenu ]\n");
        exit(1);
    }
    result->data = (int *)malloc(len * sizeof(int));
    if (result->data == NULL)
    {
        printf(" [ un probleme d'allocation de memoire est survenu ]\n");
        exit(1);
    }
    result->n = len;
    return result;
}
void free_vector(Vector *v)
{
    free(v->data);
    free(v);
}

Vector_d *create_vector(unsigned int len)
{
    Vector_d *result = (Vector_d *)malloc(sizeof(Vector_d));
    if (result == NULL)
    {
        printf(" [ un probleme d'allocation de memoire est survenu ]\n");
        exit(1);
    }
    result->data = (int *)malloc(len * sizeof(double));
    if (result->data == NULL)
    {
        printf(" [ un probleme d'allocation de memoire est survenu ]\n");
        exit(1);
    }
    result->n = len;
    return result;
}
void free_vector(Vector_d * v)
{
    free(v->data);
    free(v);
}