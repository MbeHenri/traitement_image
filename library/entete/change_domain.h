#ifndef CHANGE_DOMAIN_H_INCLUDED
#define CHANGE_DOMAIN_H_INCLUDED

#include "Complex.h"

/* permet de quitter du domaine cartesien pour le dommaine parametrique polaire suivant les echantillons de parametres beta et theta
(qui sont des vecteurs de valeurs reeles par ordre croissant) en tenant compte de la couleur qui doit definir un point dans le
plan parametrique
*/
int **transformer_hough(int **d, int n_ligne, int n_col, double *beta, int len_beta, double *theta, int len_theta, int color);

/* permt de quitter du domaine continue pour le domaine de fourier(frequentielle) sur une dimension
 */
Complex * transform_fourier_dim1(Complex* w, int n);

/* permt de quitter du domaine continue pour le domaine de fourier(frequentielle) sur deux dimensions
 */
Complex ** transform_fourier_dim2(Complex** d, int n_ligne, int n_col);

/* permt de quitter du domaine de fourier(frequentielle) vers le domaine continue(naturelle)
 */
Complex **transform_fourier_rev(Complex** d, int n_ligne, int n_col);

#endif // CHANGE_DOMAIN_H_INCLUDED