#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

//Vecteur de valeurs de pixels pour les images a niveau de gris et binaire
typedef struct Vector Vector;
struct Vector
{
    unsigned int n;
    int * data;
};

typedef struct Vector_d Vector_d;
struct Vector_d
{
    unsigned int n;
    double * data;
};

Vector* create_vector(unsigned int len);
void free_vector(Vector * v);

Vector_d* create_vector_d(unsigned int len);
void free_vector_d(Vector_d * v);

#endif