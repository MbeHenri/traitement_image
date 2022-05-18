#include <stdio.h>
#include <stdlib.h>

#include "../entete/Vector.h"

Vector *create_vector(int len)
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

Vector_d *create_vector_d(int len)
{
    Vector_d *result = (Vector_d *)malloc(sizeof(Vector_d));
    if (result == NULL)
    {
        printf(" [ un probleme d'allocation de memoire est survenu ]\n");
        exit(1);
    }
    result->data = (double *)malloc(len * sizeof(double));
    if (result->data == NULL)
    {
        printf(" [ un probleme d'allocation de memoire est survenu ]\n");
        exit(1);
    }
    result->n = len;
    return result;
}
void free_vector_d(Vector_d *v)
{
    free(v->data);
    free(v);
}

Vector_d *echantillonage(double min, double max, double ecart)
{
    int n = 1;
    // on recherche le nombre le nombre d'ecart possible partant de la valeur minimale
    while (min + ecart * n <= max)
    {
        n++;
    }
    Vector_d *result = create_vector_d(n);
    int i = 0;
    // on construit un vecteur constituant les valeurs suuccessives d'ecart
    for (i = 0; i < n; i++)
    {
        result->data[i] = min + ecart * i;
    }
    return result;
}