#ifndef SEGMENTATION_H_INCLUDED
#define SEGMENTATION_H_INCLUDED

/* algorithme permettant d'obtenir k clusters d'une matrices d'entiers par rapport*/
int **kmeans(int **d, int n_ligne, int n_col, int K, int min, int max, double e1, double e2);

/*algorithme permettant d'effectuer le seuillage simple*/
int **seuillage(int **d, int n_ligne, int n_col, double seuil);

/*algorithme permettant d'effectuer le seuillage multiple*/
int **seuillage_multiple(int **d, int n_ligne, int n_col, double* seuils, int n_seuils);

/*algorithme permettant d'effectuer le seuillage automatique par rapport a l'algo de otsu*/
int **seuillage_auto_otsu(int **d, int n_ligne, int n_col);

/* algorithmes permettant d'obtenir une zone homogene depart un germe impose */
int **germe(int **d, int n_ligne, int n_col, int x, int y,const double e);
void germe_r(int **d, int **marque,const int n_ligne,const int n_col, int x, int y,const double e);
#endif