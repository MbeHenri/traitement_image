#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"

// STRUCTURES D'IMAGES
//-----------------------

// Image binaire
typedef struct ImageB ImageB;
struct ImageB
{
    unsigned int nLigne;
    unsigned int nColonne;
    int ** data;
};

// Image a niveau de gris
typedef struct ImageG ImageG;
struct ImageG
{
    unsigned int nLigne;
    unsigned int nColonne;
    int ** data;
};

// Image a couleur
typedef struct ImageC ImageC;
struct ImageC
{
    int nLigne;
    int nColonne;
    int ** r;
    int ** g;
    int ** b;
};

// PROTOTYPES DES FONCTIONS DE LIBERATION D'ESPACE
//------------------------------------------------

/* permet de liberer l'espace de la memoire utilisee pour une image 
a niveau de gris
*/
void free_ImageG(ImageG * img);

/* permet de liberer l'espace de la memoire utilisee pour une image binaire
*/
void free_ImageB(ImageB * img);


// PROTOTYPES DES FONCTIONS DE SAUVEGARDE ET DE LECTURE D'IMAGES
//--------------------------------------------------------------

/* permet de recuperer l'image de part un pointeur sur fichier d'image binaire
*/
ImageB* read_B(FILE * f);

/* permet de sauvegarder une image binaire
*/
void write_B(ImageB* img, const char * path);

/* permet de recuperer l'image de part un pointeur sur fichier d'image a niveau de gris 
*/
ImageG* read_G(FILE * f);

/* permet de sauvegarder une image a niveau de gris 
*/
void write_G(ImageG* img, const char * path);

/* permet de recuperer l'image de part un pointeur sur fichier d'image a niveau de gris 
*/
ImageC* read_C(FILE * f);

/* permet de sauvegarder une image a niveau de gris 
*/
void write_C(ImageC* img, const char * path);


// PROTOTYPES DES FONCTIONS DE BASE D'IMAGES POUR LES IMAGES A NIVEAUX DE GRIS 
//----------------------------------------------------------------------------

/*permet d'obtenir l'histogramme d'une image a niveau de gris 
*/
int * histogram_G(ImageG *);

/*permet d'obtenir la luminance d'une image a niveau de gris 
*/
double luminance_G(ImageG *);

/*permet d'obtenir le contraste a ecart type d'une image a niveau de gris 
*/
double contraste_ecart_type_G(ImageG *);

/*permet d'obtenir le contraste min max d'une image a niveau de gris 
*/
double contraste_min_max_G(ImageG *);

/*permet d'obtenir la valeur maximale de pixels d'une image a niveau de gris 
*/
int max_G(ImageG *);

/*permet d'obtenir la valeur minimale de pixels d'une image a niveau de gris 
*/
int min_G(ImageG *);

/*permet d'obtenir la somme de deux images a niveaux de gris
*/
ImageG* plus_G(ImageG*,ImageG*);

/*permet d'obtenir la multiplication d'une image a niveau de gris avec un ratio 
[0..1]
*/
ImageG* fois_G(ImageG*,double);

/*permet d'obtenir la difference d'une image a niveau de gris sur une autre 
*/
ImageG* moins_G(ImageG*,ImageG*);

/*permet d'obtenir le profil d'intensite d'une image a niveau de gris
*/
Vector* profil_intensite_G(ImageG* , unsigned int x1 , unsigned int y1, unsigned int x2, unsigned int y2 );

/*permet de tracer le segment [(x1,y1) (x2,y2)] de niveau de gris val_replace sur l'image
*/
ImageG * draw_segmentG(ImageG*, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, int val_replace);

/*permet de tracer le circle [(x1,y1) (x2,y2)] de niveau de gris val_replace sur l'image
*/
ImageG * draw_circleG(ImageG*, unsigned int xr, unsigned int yr, double rayon, int val_replace);

/*permet d'obtenir l'inverse d'une image a niveau de gris
*/
ImageG* inverseG(ImageG* img);

/*permet de dessiner un disque sur une image a niveau de gris
*/
ImageG* drawDisqueG(ImageG* img,unsigned int xr, unsigned int yr,double rayon, int val_replace);

// PROTOTYPES DES FONCTIONS DE BASE D'IMAGES IMPLIQUANT AU MOINS DEUX TYPES D'IMAGES
//----------------------------------------------------------------------------------

/*permet de binariser l'iamage a niveau de gris de part un seuil
*/
ImageB* binarisationG(ImageG* img, double seuil);

/* permet de rendre une image binaire en image a niveau de gris
*/
ImageG* grisB(ImageB* img);

/* et logique entre une image a niveau de gris et une image binaire
*/
ImageG* etG(ImageB* img1, ImageG* img2);

/* et logique entre une image binaire et une image binaire
*/
ImageB* etB(ImageB* img1, ImageB* img2);

/* ou logique entre une image a niveau de gris et une image binaire
*/
ImageG* ouG(ImageB* img1, ImageG* img2);

/* ou logique entre une image binaire et une image binaire
*/
ImageB* ouB(ImageB* img1, ImageB* img2);
#endif // IMAGE_H_INCLUDED