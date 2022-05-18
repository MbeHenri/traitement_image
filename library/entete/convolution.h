#ifndef CONVOLUTION_H_INCLUDED
#define CONVOLUTION_H_INCLUDED

// STRUCTURE DE FILTRE, FONCTIONS Y ASSOCIEES ET LIBERATION DE MEMOIRE

/* structure de filtre
 */
typedef struct Filtre Filtre;
struct Filtre
{
    int pas;
    int **data;
};

/*permet de recuperer un filtre contenu dans un fichier texte
 */
Filtre *read_filtre(const char *path);

/*permet de rammener les valeurs de filtre dans l'intervalle [0..1]
 */
double **norm_filtre(int **filtre, int pas);

/*permet de liberer l'espace memoire associe au filtre
 */
void free_Filtre(Filtre *filtre);

// FILTRES CONNUS DYNAMIQUES

/* fitre gaussien de nombre de voisin 'pas' et d'ecart type donné
 */
int **filtre_gausien(int pas, double ecart_type);

/* fitre moyenneur de nombre de voisin 'pas'
 */
int **filtre_moyenneur(int pas);

// OPERATIONS DE CONVOLUTION

/* permet d'effectuer la convolution de l'image par rapport a un filtre quelconque donne
 */
int **convoluer(int **d, int n_ligne, int n_col, double **filtre, int pas);

/* permet d'effectuer la convolution de l'image par rapport a un filtre median
 */
int **convoluerMedian(int **d, int n_ligne, int n_col, int pas);

#endif // CONVOLUTION_H_INCLUDED