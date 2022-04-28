#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"

// PROTOTYPES DES FONCTIONS DE CREATION, DE COPIE ET DE LIBERATION D'ESPACE
//----------------------------------------------------------------

/* permet de creer de l'espace memoire pour une matrice d'entiers a 'n_ligne'
de lignes et a 'n_col' de colonnes
*/
int **create_matrix(unsigned int n_ligne, unsigned int n_col);

/* permet de copier une matrice d'entiers a 'n_ligne'
de lignes et a 'n_col' de colonnes
*/
int **copie_matrix(int** d, unsigned int n_ligne, unsigned int n_col);

/* permet de creer de l'espace memoire pour une matrice de reels a 'n_ligne'
de lignes et a 'n_col' de colonnes
*/
double **create_matrix_d(unsigned int n_ligne, unsigned int n_col);

/* permet de liberer de l'espace memoire pour une matrice d'entiers a 'n_ligne'
de lignes et a 'n_col' de colonnes
*/
void free_matrix(int **d, unsigned int n_ligne);

/* permet de liberer de l'espace memoire pour une matrice de reels a 'n_ligne'
de lignes et a 'n_col' de colonnes
*/
void free_matrix_d(double **d, unsigned int n_ligne);


// PROTOTYPES DES FONCTIONS DE BASE POUR LE TRAITEMENT SUR IMAGE
//--------------------------------------------------------------

/* permet d'effectuer un echantillonage d'un intervalle [ min .. max ] 
    suivant une valeur d' ecart
*/
Vector_d* echantillonage(double min, double max, double ecart);

/* permet d'obtenir l'histogramme des valeurs d'une matrice d'entiers
*/
int *histogram(int **d, unsigned int n_ligne, unsigned int n_col);

/* permet d'obtenir la luminance (moyennne) d'une matrice d'entiers 
*/
double luminance(int **d, unsigned int n_ligne, unsigned int n_col);

/* permet d'obtenir l'ecert typo (moyennne) d'une matrice d'entiers 
*/
double contraste_ecart_type(int **d, unsigned int n_ligne, unsigned int n_col);

/* permet d'obtenir le contraste min max d'une matrice d'entiers 
*/
double contraste_min_max(int **d, unsigned int n_ligne, unsigned int n_col);

/* permet d'obtenir le maximum d'une matrice d'entiers 
*/
int max_(int **d, unsigned int n_ligne, unsigned int n_col);

/* permet d'obtenir le minimum d'une matrice d'entiers 
*/
int min_(int **d, unsigned int n_ligne, unsigned int n_col);

/* permet d'obtenir le resultat de la somme de deux matrices d'entiers 
*/
int **plus_(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col);

/* permet d'obtenir le resultat du produit d'une matrice d'entiers avec unn ratio [ 0..1 ] 
*/
int **fois_(int ** d_, unsigned int n_ligne, unsigned int n_col1, double ratio);

/* permet d'obtenir le resultat de la soustraction de deux matrices d'entiers 
*/
int **moins_(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col);

/* permet d'obtenir le resultat du 'et' logique d'une matrice de noir = 1 et de blanc = 0 et de n'importe quelle matrice d'entiers  
*/
int **et_(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col, int a);

/* permet d'obtenir le resultat du 'ou' logique d'une matrice de noir = 1 et de blanc = 0 et de n'importe quelle matrice d'entiers  
*/
int **ou_(int **d1, int **d2, unsigned int n_ligne, unsigned int n_col, int a);

/* permet d'obtenir le resultat de la difference d'une matrice a une autre, la premiere 
rempli de a
*/
int ** difference(int** d, unsigned int n_ligne, unsigned int n_col, int a);

/* permet d'obtenir le profil d'intensite d'un segment [(x1,y1) (x2,y2)]
*/
Vector *profil_intensite_(int **d, unsigned int n_ligne, unsigned int n_col, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

/* permet de remplacer par 'val_replace' les valeurs du segment [(x1,y1) (x2,y2)]
*/
int ** replace_line_(int **d, unsigned int n_ligne, unsigned int n_col, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, int val_replace);

/* permet de remplacer par 'val_replace' les valeurs du disque ((xr,yr), rayon)
*/
int **replace_circle_(int **d, unsigned int n_ligne, unsigned int n_col, unsigned int xr, unsigned int yr, double rayon , int val_replace);

/* permet de remplacer par 'val_replace' les valeurs du disque ((xr,yr), rayon)
*/
int **replace_disque_(int **d, unsigned int n_ligne, unsigned int n_col, unsigned int xr, unsigned int yr, double rayon , int val_replace);

/* permet d'obtenir d'une matrice d'entiers et d'un seuil dans ]0, 255[ 
une matrice de valeurs {0, 1} tel que si on a la valeur d'un entier est inferieur a 
'seuil' alors ona 1, et 0 sinon
*/
int ** binarisation(int** d, unsigned int n_ligne, unsigned int n_col, double seuil);

/* permet de chenger l'intervalle de valeur de cellulle comprise dans l'intervalle [ a1.. a2] vers [min .. max]
ces intervalles etant inclus dans l'intervalle [ 0..255]
*/
int ** changer_plage(int** d, unsigned int n_ligne, unsigned int n_col,  int a1,  int a2,  int min,  int max);

#endif // BASE_H_INCLUDED