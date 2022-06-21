#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#define PI 3.141592653589793
#include "Vector.h"

// PROTOTYPES DES FONCTIONS DE CREATION, DE COPIE ET DE LIBERATION D'ESPACE
//----------------------------------------------------------------

/* permet de creer de l'espace memoire pour une matrice d'entiers a 'n_ligne'
de lignes et a 'n_col' de colonnes
*/
int **create_matrix(int n_ligne, int n_col);

/* permet de copier une matrice d'entiers a 'n_ligne'
de lignes et a 'n_col' de colonnes
*/
int **copie_matrix(int **d, int n_ligne, int n_col);

/* permet de creer de l'espace memoire pour une matrice de reels a 'n_ligne'
de lignes et a 'n_col' de colonnes
*/
double **create_matrix_d(int n_ligne, int n_col);

/* permet de liberer de l'espace memoire pour une matrice d'entiers a 'n_ligne'
de lignes et a 'n_col' de colonnes
*/
void free_matrix(int **d, int n_ligne);

/* permet de liberer de l'espace memoire pour une matrice de reels a 'n_ligne'
de lignes et a 'n_col' de colonnes
*/
void free_matrix_d(double **d, int n_ligne);

// PROTOTYPES DES FONCTIONS DE BASE POUR LE TRAITEMENT SUR IMAGE
//--------------------------------------------------------------

/* permet d'obtenir l'histogramme des valeurs d'une matrice d'entiers
 */
int *histogram(int **d, int n_ligne, int n_col);

/* permet d'obtenir la luminance (moyennne) d'une matrice d'entiers
 */
double luminance(int **d, int n_ligne, int n_col);

/* permet d'obtenir l'ecert typo (moyennne) d'une matrice d'entiers
 */
double contraste_ecart_type(int **d, int n_ligne, int n_col);

/* permet d'obtenir le contraste min max d'une matrice d'entiers
 */
double contraste_min_max(int **d, int n_ligne, int n_col);

/* permet d'obtenir le resultat de la somme de deux matrices d'entiers
 */
int **plus_(int **d1, int **d2, int n_ligne, int n_col);

/* permet d'obtenir le resultat du produit d'une matrice d'entiers avec unn ratio [ 0..1 ]
 */
int **fois_(int **d_, int n_ligne, int n_col1, double ratio);

/* permet d'obtenir le resultat de la soustraction de deux matrices d'entiers
 */
int **moins_(int **d1, int **d2, int n_ligne, int n_col);

/* permet d'obtenir le resultat du 'et' logique d'une matrice de noir = 1 et de blanc = 0 et de n'importe quelle matrice d'entiers
 */
int **et_(int **d1, int **d2, int n_ligne, int n_col, int a);

/* permet d'obtenir le resultat du 'ou' logique d'une matrice de noir = 1 et de blanc = 0 et de n'importe quelle matrice d'entiers
 */
int **ou_(int **d1, int **d2, int n_ligne, int n_col, int a);

/* permet d'obtenir le profil d'intensite d'un segment [(x1,y1) (x2,y2)]
 */
int**profil_intensite_(int **d, int x1, int y1, int x2, int y2, int* len);

/* permet d'obtenir d'une matrice d'entiers et d'un seuil dans ]0, 255[
une matrice de valeurs {0, 1} tel que si on a la valeur d'un entier est inferieur a
'seuil' alors ona 1, et 0 sinon
*/
int **binarisation(int **d, int n_ligne, int n_col, double seuil);

// PROTOTYPES DES FONCTIONS DE BASE
//---------------------------------

/* permet d'obtenir un vecteur crier de part un vecteur de depart
 */
void sortTab(int *d, int n);
int compare(const void * a, const void * b);
/* permet d'obtenir le maximum d'une matrice d'entiers
 */
int max_(int **d, int n_ligne, int n_col);

/* permet d'obtenir le minimum d'une matrice d'entiers
 */
int min_(int **d, int n_ligne, int n_col);

/* permet d'obtenir l'indice de la valeur la plus proche a 'val' dans le tableau d
 */
int indice_val_proche(double *d, int len, double val);

/* permet d'obtenir le resultat de la difference d'une matrice a une autre, la premiere
rempli de a
*/
int **difference(int **d, int n_ligne, int n_col, int a);

/* permet de remplacer par 'val_replace' les valeurs du segment [(x1,y1) (x2,y2)] (on met dans une autre matrice)
 */
int **replace_line_(int **d, int n_ligne, int n_col, int x1, int y1, int x2, int y2, int val_replace);

/* permet de remplacer par 'val_replace' les valeurs du segment [(x1,y1) (x2,y2)]
 */
void replace_on_line_(int **d, int x1, int y1, int x2, int y2, int val_replace);

/* permet de remplacer par 'val_replace' les valeurs du disque ((xr,yr), rayon) (on met dans une autre matrice)
 */
int **replace_circle_(int **d, int n_ligne, int n_col, int xr, int yr, double rayon, int val_replace);

/* permet de remplacer par 'val_replace' les valeurs du disque ((xr,yr), rayon) (on met dans une autre matrice)
 */
int **replace_disque_(int **d, int n_ligne, int n_col, int xr, int yr, double rayon, int val_replace);

/* permet de remplacer par 'val_replace' les valeurs du rectangle ((xr,yr), longueur, largeur) (on met dans une autre matrice)
 */
int **replace_rectangle_(int **d, int n_ligne, int n_col, int xr, int yr, double longueur, double largueur, int val_replace);

/* permet de remplacer par 'val_replace' les valeurs du disque ((xr,yr), rayon)
 */
void replace_on_disque_(int **d, int n_ligne, int n_col, int xr, int yr, double rayon, int val_in, int val_e);

/* permet de remplacer par 'val_replace' les valeurs du rectangle ((xr,yr), longueur, largeur)
 */
void replace_on_rectangle_(int **d, int n_ligne, int n_col, int xr, int yr, double longueur, double largeur, int val_in);

/* permet de changer lineairement l'intervalle de valeur des cellules comprises dans l'intervalle [ a1.. a2] vers [min .. max]
ces intervalles etant inclus dans l'intervalle [ 0..255] eventuellement
*/
int **changer_plage(int **d, int n_ligne, int n_col, int a1, int a2, int min, int max);

/* permet d'avoir les indices des k plus grande valeurs d'une matrice d'entiers*/
int **selection_k_max(int **d, int n_ligne, int n_col, int k);

/* permet d'obtenir une matrice d'entier issues d'un ensemble de valeurs ordonnees pour une image */
int**matrice_hist(int nbpixels,int* hist, int len_hist, int ecart_x, int esp_haut, int esp_gauche, int esp_bas, int esp_droite, int longeur, int val_rep, int val_in);

/* permet d'obtenir une matrice d'entier issues d'un ensemble de valeurs ordonnees pour une image */
int**matrice_profil(int nbpixels,int* prof, int len_prof, int ecart_x, int esp_haut, int esp_gauche, int esp_bas, int esp_droite, int longeur, int val_rep, int val_in);

//moyenne de vecteur d'entier
int moy_v(int* v, int n);
#endif // BASE_H_INCLUDED