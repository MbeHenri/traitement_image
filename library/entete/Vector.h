#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

// STRUCTURES DE VECTEURS
//-----------------------

/*Vecteur de 'n' entiers
*/
typedef struct Vector Vector;
struct Vector
{
    unsigned int n;
    int * data;
};

/*Vecteur de 'n' reels
*/
typedef struct Vector_d Vector_d;
struct Vector_d
{
    unsigned int n;
    double * data;
};

// PROTOTYPES DES FONCTIONS DE CREATION ET DE LIBERATION D'ESPACE
//----------------------------------------------------------------

/* permet de creer de l'espace memoire pour un vecteur d'entiers 
*/
Vector* create_vector(unsigned int len);

/* permet de liberer de l'espace memoire pour un vecteur d'entiers 
*/
void free_vector(Vector * v);

/* permet de creer de l'espace memoire pour un vecteur de reels
*/
Vector_d* create_vector_d(unsigned int len);

/* permet de liberer de l'espace memoire pour un vecteur de rells
*/
void free_vector_d(Vector_d * v);


// PROTOTYPES DES FONCTIONS DE VECTEUR UNIQUEMENT
//----------------------------------------------------------------
/* permet d'effectuer un echantillonage d'un intervalle [ min .. max ] 
    suivant une valeur d' ecart
*/
Vector_d* echantillonage(double min, double max, double ecart);

#endif