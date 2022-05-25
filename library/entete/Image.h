#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Vector.h"
#include "convolution.h"

// STRUCTURES D'IMAGES
//-----------------------

// Image binaire
typedef struct ImageB ImageB;
struct ImageB
{
    int nLigne;
    int nColonne;
    int **data;
};

// Image a niveau de gris
typedef struct ImageG ImageG;
struct ImageG
{
    int nLigne;
    int nColonne;
    int **data;
};

// Image a couleur
typedef struct ImageC ImageC;
struct ImageC
{
    int nLigne;
    int nColonne;
    int **r;
    int **g;
    int **b;
};

// PROTOTYPES DES FONCTIONS DE LIBERATION D'ESPACE
//------------------------------------------------

/* permet de liberer l'espace de la memoire utilisee pour une image
a niveau de gris
*/
void free_ImageG(ImageG *img);

/* permet de liberer l'espace de la memoire utilisee pour une image binaire
 */
void free_ImageB(ImageB *img);

/* permet de liberer l'espace de la memoire utilisee pour une image couleur
 */
void free_ImageC(ImageC *img);

// PROTOTYPES DES FONCTIONS DE SAUVEGARDE ET DE LECTURE D'IMAGES
//--------------------------------------------------------------

/* permet de recuperer l'image de part un pointeur sur fichier d'image binaire
 */
ImageB *read_B(FILE *f);

/* permet de sauvegarder une image binaire
 */
void write_B(ImageB *img, const char *path);

/* permet de recuperer l'image de part un pointeur sur fichier d'image a niveau de gris
 */
ImageG *read_G(FILE *f);

/* permet de sauvegarder une image a niveau de gris
 */
void write_G(ImageG *img, const char *path);

/* permet de recuperer l'image de part un pointeur sur fichier d'image a niveau de gris
 */
ImageC *read_C(FILE *f);

/* permet de sauvegarder une image a niveau de gris
 */
void write_C(ImageC *img, const char *path);

// PROTOTYPES DES FONCTIONS DE BASE D'IMAGES POUR LES IMAGES BINAIRES
//-------------------------------------------------------------------

/*permet dobtenir la matrice d'occurence dans le domaine parametrique de hough pour une image binaire
 */
int **transform_hough_occur(ImageB *img, Vector_d *beta, Vector_d *theta, int color);

// PROTOTYPES DES FONCTIONS DE BASE D'IMAGES POUR LES IMAGES A NIVEAUX DE GRIS
//----------------------------------------------------------------------------

/*permet d'obtenir l'histogramme d'une image a niveau de gris
 */
int *histogram_G(ImageG *);

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
ImageG *plus_G(ImageG *, ImageG *);

/*permet d'obtenir la multiplication d'une image a niveau de gris avec un ratio
[0..1]
*/
ImageG *fois_G(ImageG *, double);

/*permet d'obtenir la difference d'une image a niveau de gris sur une autre
 */
ImageG *moins_G(ImageG *, ImageG *);

/*permet d'obtenir le profil d'intensite d'une image a niveau de gris
 */
int**profil_intensite_G(ImageG *, int x1, int y1, int x2, int y, int* len);

/*permet de tracer le segment [(x1,y1) (x2,y2)] de niveau de gris val_replace sur l'image
 */
void draw_segmentG(ImageG *, int x1, int y1, int x2, int y2, int val_replace);

/*permet de tracer le circle [(x1,y1) (x2,y2)] de niveau de gris val_replace sur l'image
 */
ImageG* draw_circleG(ImageG *, int xr, int yr, double rayon, int val_replace);

/*permet d'obtenir l'inverse d'une image a niveau de gris
 */
ImageG *inverseG(ImageG *img);

/*permet de dessiner un disque sur une image a niveau de gris
 */
void drawDisqueG(ImageG *img, int xr, int yr, double rayon, int val_replace);

/*permet de dessiner un rectangle plein sur une image a niveau de gris
 */
void drawRectangleG(ImageG *img, int xr, int yr, double longueur, double largeur, int val_replace);

/*permet de realiser l'operation de convolution d'une image a niveau de gris et d'un filtre
 */
ImageG *convolutionG(ImageG *img, Filtre *filtre);

/*permet de realiser l'operation de convolution d'une image a niveau de gris et d'un filtre
 */
ImageG *convolutionMedianG(ImageG *img, int pas);

/*permet de convertir une matrice d'entier en une image
 */
ImageG *convert_matrixG(int **d, int n_ligne, int n_col);

/*permet d'egaliser l'histogramme d'une image
 */
ImageG *egaliser_G(ImageG *img);

/*permet d'effectuer la transformation lineaire d'une image
 */
ImageG *transform_lineaire_G(ImageG *img);

/*permet d'effectuer la transformation lineaire avec saturation d'une image
 */
ImageG *transform_lineaire_satur_G(ImageG *img, int s_min, int s_max);

/*permet d'effectuer la transformation lineaire avec saturation d'une image
 */
ImageG *transform_lineaire_morceau_G(ImageG *img, int *s, int *v, int len_s);

/*permet d'obtenir l'image obtenus apres regroupement grace a l'algorithme kmeans
 */
ImageG *kmeansG(ImageG *img, int K, double e1, double e2);

/*permet d'obtenir la region ici du germe (x,y) sur l'image
 */
ImageG *germeG(ImageG *img, int x, int y, double e);

/*permet d'obtenir une image agrandit de l'image de depart k fois plus grande*/
ImageG *interpolation_knnG(ImageG *img, int k);

/*permet d'obtenir une image agrandit de l'image de depart k fois plus grande*/
ImageG *interpolation_bilG(ImageG *img);

// PROTOTYPES DES FONCTIONS DE BASE D'IMAGES POUR LES IMAGES COULEURS
//-------------------------------------------------------------------
/*permet d'obtenir un histogramme en couleur depuis un ensemble d'entiers*/
ImageC* histogrameGC(int* hist, int len);

/*permet d'obtenir un profil en couleur depuis un ensemble d'entiers*/
ImageC* profilGC(int* prof, int len);

// PROTOTYPES DES FONCTIONS DE BASE D'IMAGES IMPLIQUANT AU MOINS DEUX TYPES D'IMAGES
//----------------------------------------------------------------------------------

/*permet de binariser l'iamage a niveau de gris de part un seuil
 */
ImageB *binarisationG(ImageG *img, double seuil);

/* permet de rendre une image binaire en image a niveau de gris
 */
ImageG *grisB(ImageB *img);

/* et logique entre une image a niveau de gris et une image binaire
 */
ImageG *etG(ImageB *img1, ImageG *img2);

/* et logique entre une image binaire et une image binaire
 */
ImageB *etB(ImageB *img1, ImageB *img2);

/* ou logique entre une image a niveau de gris et une image binaire
 */
ImageG *ouG(ImageB *img1, ImageG *img2);

/* ou logique entre une image binaire et une image binaire
 */
ImageB *ouB(ImageB *img1, ImageB *img2);

/*PAS ENCORE TERMINE*/
/*permet d' obtenir la matrice de la partie reelle du spectre de fourier
 */
int **matrix_spectre_fourier_reelle(ImageG *img);

/*permet d' obtenir la matrice de la partie imaginaire du spectre de fourier
 */
int **matrix_spectre_fourier_imaginaire(ImageG *img);
/*permet de retourner dans le domaine discret de part le domaine frequentiel de fourier
grace aux images de la partie imaginaire et reelle du spectre de fourier
-- pour des images a niveaux de gris
 */
ImageG *transform_fourier_revG(ImageG *img_f_reelle, ImageG *img_f_imaginaire);
#endif // IMAGE_H_INCLUDED