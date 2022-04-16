#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"
/*
    STRUCTURES LIEES AUx IMAGES
*/

// Structure d'une couleur
typedef struct Couleur Couleur;
struct Couleur
{
    int r;
    int g;
    int b;  
};

// Image binaire et Image a niveau de gris 
typedef struct ImageG ImageG;
struct ImageG
{
    unsigned int nLigne;
    unsigned int nColonne;
    unsigned int ** data;
};

// Image a couleur
typedef struct ImageC ImageC;
struct ImageC
{
    int nLigne;
    int nColonne;
    Couleur ** data;
};

// prototype de liberation de la memoire
void free_ImageG(ImageG *);

//prototype de lecture 
ImageG* read_G(FILE *);

//prototype de fonction de base
unsigned int * histogram_G(ImageG *);
double luminance_G(ImageG *);
double contraste_ecart_type_G(ImageG *);
double contraste_min_max_G(ImageG *);
unsigned int max_G(ImageG *);
unsigned int min_G(ImageG *);

ImageG* plus(ImageG*,ImageG*);
ImageG* fois(ImageG*,double);
ImageG* moins(ImageG*,ImageG*);


Vector* profil_intensite(ImageG* , unsigned int x1 , unsigned int y1, unsigned int x2, unsigned int y2 );


#endif // IMAGE_H_INCLUDED