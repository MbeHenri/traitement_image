#ifndef SEGMENTATION_H_INCLUDED
#define SEGMENTATION_H_INCLUDED

/* algorithme permettant d'obtenir k clusters d'une matrices d'entiers par rapport*/
int **kmeans(int **d, int n_ligne, int n_col, int K, int min, int max, double e1, double e2);

/* algorithmes permettant d'obtenir une zone homogene depart un germe impose */
int **germe(int **d, int n_ligne, int n_col, int x, int y,const double e);
void germe_r(int **d, int **marque,const int n_ligne,const int n_col, int x, int y,const double e);
#endif