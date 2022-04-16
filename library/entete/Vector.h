#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

//Vecteur de valeurs de pixels pour les images a niveau de gris et binaire
typedef struct Vector Vector;
struct Vector
{
    unsigned int n;
    unsigned int * data;
};

#endif