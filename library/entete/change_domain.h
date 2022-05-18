#ifndef CHANGE_DOMAIN_H_INCLUDED
#define CHANGE_DOMAIN_H_INCLUDED

/* permet de quitter du domaine cartesien pour le dommaine parametrique polaire suivant les echantillons de parametres beta et theta
(qui sont des vecteurs de valeurs reeles par ordre croissant) en tenant compte de la couleur qui doit definir un point dans le
plan parametrique
*/
int **transformer_hough(int **d, int n_ligne, int n_col, double *beta, int len_beta, double *theta, int len_theta, int color);

/* permt de quitter du domaine continue pour le domaine de fourier(frequentielle) pour la partie reelle
 */
int **transform_fourier_reelle(int **d, int n_ligne, int n_col);

/* permet de quitter du domaine continue pour le domaine de fourier(frequentielle) pour la partie imaginaire
 */
int **transform_fourier_imaginaire(int **d, int n_ligne, int n_col);

/* permt de quitter du domaine de fourier(frequentielle) vers le domaine continue(naturelle)
 */
int **transform_fourier_rev(int **d_reelle, int **d_imaginaire, int n_ligne, int n_col);

#endif // CHANGE_DOMAIN_H_INCLUDED