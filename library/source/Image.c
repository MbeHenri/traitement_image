#include <stdlib.h>
#include <stdio.h>

#include "../entete/Image.h"
#include "../entete/base.h"
#include "../entete/change_domain.h"
#include "../entete/transformation.h"
#include "../entete/segmentation.h"

void free_ImageG(ImageG *img)
{
    free_matrix(img->data, img->nLigne);
    free(img);
}
void free_ImageB(ImageB *img)
{
    free_matrix(img->data, img->nLigne);
    free(img);
}
void free_ImageC(ImageC *img)
{
    free_matrix(img->r, img->nLigne);
    free_matrix(img->g, img->nLigne);
    free_matrix(img->b, img->nLigne);
    free(img);
}

ImageG *read_G(FILE *f)
{
    ImageG *img = (ImageG *)malloc(sizeof(ImageG));
    if (img == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour l'image ]\n");
        exit(1);
    }
    while (fgetc(f) == '#')
    {
        while (getc(f) != '\n')
            ;
    }
    int max;
    fseek(f, -1, SEEK_CUR);
    fscanf(f, "%d %d", &img->nColonne, &img->nLigne);
    img->data = create_matrix(img->nLigne, img->nColonne);
    fscanf(f, "%d", &max);
    int i, j;
    for (i = 0; i < img->nLigne; i++)
        for (j = 0; j < img->nColonne; j++)
            fscanf(f, "%d", &img->data[i][j]);

    return img;
}
ImageB *read_B(FILE *f)
{
    ImageB *img = (ImageB *)malloc(sizeof(ImageB));
    if (img == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour l'image ]\n");
        exit(1);
    }
    while (fgetc(f) == '#')
    {
        while (getc(f) != '\n')
            ;
    }
    fseek(f, -1, SEEK_CUR);

    fscanf(f, "%d %d\n", &img->nColonne, &img->nLigne);
    img->data = create_matrix(img->nLigne, img->nColonne);
    int i, j;
    for (i = 0; i < img->nLigne; i++)
    {
        for (j = 0; j < img->nColonne; j++)
        {
            char c = fgetc(f);
            if (c == '0')
            {
                img->data[i][j] = 0;
            }
            else if (c == '1')
            {
                img->data[i][j] = 1;
            }
            else
            {
                c = fgetc(f);
                if (c == '0')
                    img->data[i][j] = 0;
                else
                    img->data[i][j] = 1;
            }
        }
    }
    return img;
}

ImageC *read_C(FILE *f)
{
    ImageC *img = (ImageC *)malloc(sizeof(ImageC));
    if (img == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour l'image ]\n");
        exit(1);
    }
    while (fgetc(f) == '#')
    {
        while (getc(f) != '\n')
            ;
    }
    int max;
    fseek(f, -1, SEEK_CUR);
    fscanf(f, "%d %d", &img->nColonne, &img->nLigne);
    img->r = create_matrix(img->nLigne, img->nColonne);
    img->g = create_matrix(img->nLigne, img->nColonne);
    img->b = create_matrix(img->nLigne, img->nColonne);
    fscanf(f, "%d", &max);
    int i, j;
    for (i = 0; i < img->nLigne; i++)
    {
        for (j = 0; j < img->nColonne; j++)
        {
            fscanf(f, "%d", &img->r[i][j]);
            fscanf(f, "%d", &img->g[i][j]);
            fscanf(f, "%d", &img->b[i][j]);
        }
    }
    return img;
}
void write_G(ImageG *img, const char *path)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
    {
        exit(1);
    }
    fprintf(f, "P2\n");
    fprintf(f, "# realisation de Mbe\n");
    fprintf(f, "%d %d\n", img->nColonne, img->nLigne);
    fprintf(f, "%d\n", 255);
    int i, j;
    for (i = 0; i < img->nLigne; i++)
    {
        for (j = 0; j < img->nColonne; j++)
        {
            fprintf(f, "%d\n", img->data[i][j]);
        }
    }
    fclose(f);
}
void write_C(ImageC *img, const char *path)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
    {
        exit(1);
    }
    fprintf(f, "P3\n");
    fprintf(f, "# realisation de Mbe\n");
    fprintf(f, "%d %d\n", img->nColonne, img->nLigne);
    fprintf(f, "%d\n", 255);
    int i, j;
    for (i = 0; i < img->nLigne; i++)
    {
        for (j = 0; j < img->nColonne; j++)
        {
            fprintf(f, "%d\n", img->r[i][j]);
            fprintf(f, "%d\n", img->g[i][j]);
            fprintf(f, "%d\n", img->b[i][j]);
        }
    }
    fclose(f);
}

void write_B(ImageB *img, const char *path)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
    {
        exit(1);
    }
    fprintf(f, "P1\n");
    fprintf(f, "# realisation de Mbe\n");
    fprintf(f, "%d %d\n", img->nColonne, img->nLigne);
    int i, j;
    for (i = 0; i < img->nLigne; i++)
    {
        for (j = 0; j < img->nColonne; j++)
        {
            if (img->data[i][j] == 0)
                fprintf(f, "0");
            else
                fprintf(f, "1");
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int *histogram_G(ImageG *img)
{
    return histogram(img->data, img->nLigne, img->nColonne);
}

double luminance_G(ImageG *img)
{
    return luminance(img->data, img->nLigne, img->nColonne);
}
int max_G(ImageG *img)
{
    return max_(img->data, img->nLigne, img->nColonne);
}
int min_G(ImageG *img)
{
    return min_(img->data, img->nLigne, img->nColonne);
}

double contraste_ecart_type_G(ImageG *img)
{
    return contraste_ecart_type(img->data, img->nLigne, img->nColonne);
}

double contraste_min_max_G(ImageG *img)
{
    return contraste_min_max(img->data, img->nLigne, img->nColonne);
}

ImageG *plus_G(ImageG *img1, ImageG *img2)
{
    if (img1->nLigne != img2->nLigne && img1->nColonne != img2->nColonne)
    {
        printf(" [ les images n'ont pas la meme dimension ]\n");
        exit(1);
    }
    ImageG *img = (ImageG *)malloc(sizeof(ImageG));
    if (img == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour l'image resultante ]\n");
        exit(1);
    }
    img->nLigne = img1->nLigne;
    img->nColonne = img1->nColonne;
    img->data = plus_(img1->data, img2->data, img->nLigne, img->nColonne);
    return img;
}
ImageG *fois_G(ImageG *imgd, double ratio)
{
    ImageG *img = (ImageG *)malloc(sizeof(ImageG));
    if (img == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour l'image resultante ]\n");
        exit(1);
    }
    img->nLigne = imgd->nLigne;
    img->nColonne = imgd->nColonne;
    img->data = fois_(imgd->data, img->nLigne, img->nColonne, ratio);
    return img;
}
ImageG *moins_G(ImageG *img1, ImageG *img2)
{
    if (img1->nLigne != img2->nLigne && img1->nColonne != img2->nColonne)
    {
        printf(" [ les images n'ont pas la meme dimension ]\n");
        exit(1);
    }
    ImageG *img = (ImageG *)malloc(sizeof(ImageG));
    if (img == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour l'image resultante ]\n");
        exit(1);
    }
    img->nLigne = img1->nLigne;
    img->nColonne = img1->nColonne;
    img->data = moins_(img1->data, img2->data, img->nLigne, img->nColonne);
    return img;
}

int **profil_intensite_G(ImageG *img, int x1, int y1, int x2, int y2, int *len)
{
    return profil_intensite_(img->data, x1, y1, x2, y2, len);
}

void draw_segmentG(ImageG *img, int x1, int y1, int x2, int y2, int val_replace)
{
    replace_on_line_(img->data, x1, y1, x2, y2, val_replace);
}
ImageG *draw_circleG(ImageG *img, int xr, int yr, double rayon, int val_replace)
{
    ImageG *r = (ImageG *)malloc(sizeof(ImageG));
    if (r == NULL)
    {
        printf("[ il est impossible d'allouer de la memoire pour l'image resultante ]\n");
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = replace_circle_(img->data, img->nLigne, img->nColonne, xr, yr, rayon, val_replace);
    return r;
}

void drawDisqueG(ImageG *img, int xr, int yr, double rayon, int val_replace)
{
    replace_on_disque_(img->data, img->nLigne, img->nColonne, xr, yr, rayon, val_replace, val_replace);
}

void drawRectangleG(ImageG *img, int xr, int yr, double longueur, double largeur, int val_replace)
{
    replace_on_rectangle_(img->data, img->nLigne, img->nColonne, xr, yr, longueur, largeur, val_replace);
}

ImageB *binarisationG(ImageG *img, double seuil)
{
    ImageB *r = malloc(sizeof(ImageB));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = binarisation(img->data, img->nLigne, img->nColonne, seuil);
    return r;
}
ImageG *seuillageG(ImageG *img, double seuil)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = seuillage(img->data, img->nLigne, img->nColonne, seuil);
    return r;
}
ImageG *seuillage_multipleG(ImageG *img, double *seuils, int n)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = seuillage_multiple(img->data, img->nLigne, img->nColonne, seuils, n);
    return r;
}
ImageG *seuillage_auto_otsuG(ImageG *img)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = seuillage_auto_otsu(img->data, img->nLigne, img->nColonne);
    return r;
}
ImageG *grisB(ImageB *img)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    int **aux = changer_plage(img->data, img->nLigne, img->nColonne, 0, 1, 0, 255);
    r->data = difference(aux, img->nLigne, img->nColonne, 255);
    free_matrix(aux, img->nLigne);
    return r;
}
ImageG *inverseG(ImageG *img)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = difference(img->data, img->nLigne, img->nColonne, 255);
    return r;
}
ImageG *etG(ImageB *img1, ImageG *img2)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img1->nLigne;
    r->nColonne = img1->nColonne;
    r->data = et_(img1->data, img2->data, img1->nLigne, img1->nColonne, 0);
    return r;
}
ImageB *etB(ImageB *img1, ImageB *img2)
{
    ImageB *r = malloc(sizeof(ImageB));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img1->nLigne;
    r->nColonne = img1->nColonne;
    r->data = et_(img1->data, img2->data, img1->nLigne, img1->nColonne, 1);
    return r;
}
ImageG *ouG(ImageB *img1, ImageG *img2)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img1->nLigne;
    r->nColonne = img1->nColonne;
    r->data = ou_(img1->data, img2->data, img1->nLigne, img1->nColonne, 255);
    return r;
}
ImageB *ouB(ImageB *img1, ImageB *img2)
{
    ImageB *r = malloc(sizeof(ImageB));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img1->nLigne;
    r->nColonne = img1->nColonne;
    r->data = ou_(img1->data, img2->data, img1->nLigne, img1->nColonne, 0);
    return r;
}
ImageG *convolutionG(ImageG *img, Filtre *filtre)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    double **dFiltre = norm_filtre(filtre->data, filtre->pas);

    r->data = convoluer(img->data, img->nLigne, img->nColonne, dFiltre, filtre->pas);
    free_matrix_d(dFiltre, 2 * filtre->pas + 1);
    return r;
}
ImageG *convolutionMedianG(ImageG *img, int pas)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = convoluerMedian(img->data, img->nLigne, img->nColonne, pas);
    return r;
}
ImageG *convolutionGaussG(ImageG *img, int pas, int ecart_type)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    int **filtreGauss = filtre_gausien(pas, ecart_type);
    double **filtreGauss_norm = norm_filtre(filtreGauss, pas);
    free_matrix(filtreGauss, 2 * pas + 1);
    r->data = convoluer(img->data, img->nLigne, img->nColonne, filtreGauss_norm, pas);
    free_matrix_d(filtreGauss_norm, 2 * pas + 1);
    return r;
}
ImageG *convolutionMoyG(ImageG *img, int pas)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    int **filtreMoy = filtre_moyenneur(pas);
    double **filtreMoy_norm = norm_filtre(filtreMoy, pas);
    free_matrix(filtreMoy, 2 * pas + 1);
    r->data = convoluer(img->data, img->nLigne, img->nColonne, filtreMoy_norm, pas);
    free_matrix_d(filtreMoy_norm, 2 * pas + 1);
    return r;
}

int **transform_hough_occur(ImageB *img, Vector_d *beta, Vector_d *theta, int color)
{
    return transformer_hough(img->data, img->nLigne, img->nColonne, beta->data, beta->n, theta->data, theta->n, color);
}
ImageG *convert_matrixG(int **d, int n_ligne, int n_col)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = n_ligne;
    r->nColonne = n_col;
    r->data = changer_plage(d, n_ligne, n_col, min_(d, n_ligne, n_col), max_(d, n_ligne, n_col), 0, 255);
    return r;
}

Complex **spectre_fourier(ImageG *img, int* new_nligne, int* new_nCol)
{
    *new_nligne = pusisance_sup_2(img->nLigne); *new_nCol = pusisance_sup_2(img->nColonne);
    Complex** aux =NULL;
    if (*new_nligne != img->nLigne || *new_nCol != img->nColonne)
    {
        int ** new_d = create_matrix(*new_nligne,*new_nCol);
        int i=0,j=0;
        for (i = 0; i < img->nLigne; i++)
            for (j = 0; j < img->nColonne; j++)
                new_d[i][j]=img->data[i][j];
                
        for (i = img->nLigne; i < *new_nligne; i++)
            for (j = img->nColonne; j < *new_nCol; j++)
                new_d[i][j]=0;    
                
        aux = convert_matrix_int_to_complex(new_d,*new_nligne,*new_nCol);
        free_matrix(new_d,*new_nligne);
    }else{
        aux = convert_matrix_int_to_complex(img->data,*new_nligne,*new_nCol);
    }
    Complex** resultat = transform_fourier_dim2(aux, *new_nligne, *new_nCol);
    free_matrix_complex(aux,*new_nligne,*new_nCol);
    return resultat;
}

ImageG *egaliser_G(ImageG *img)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = egalizer_hist(img->data, img->nLigne, img->nColonne);
    return r;
}
ImageG *transform_lineaire_G(ImageG *img)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = transform_linear(img->data, img->nLigne, img->nColonne);
    return r;
}
ImageG *transform_lineaire_satur_G(ImageG *img, int s_min, int s_max)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = transform_linear_satur(img->data, img->nLigne, img->nColonne, s_min, s_max);
    return r;
}
ImageG *transform_lineaire_morceau_G(ImageG *img, int *s, int *v, int len)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    sortTab(s, len);
    sortTab(v, len);
    r->data = transform_linear_morceau(img->data, img->nLigne, img->nColonne, s, v, len);
    return r;
}

ImageG *kmeansG(ImageG *img, int K, double e1, double e2)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = kmeans(img->data, img->nLigne, img->nColonne, K, 0, 255, e1, e2);
    return r;
}
ImageG *germeG(ImageG *img, int x, int y, double e)
{
    ImageG *r = malloc(sizeof(ImageB));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne;
    r->nColonne = img->nColonne;
    r->data = germe(img->data, img->nLigne, img->nColonne, x, y, e);
    ImageB *b = binarisationG(r, 50);
    free_ImageG(r);
    r = ouG(b, img);
    free_ImageB(b);
    return r;
}

ImageC *histogrameGC(int *hist, int len)
{
    ImageC *img = malloc(sizeof(ImageC));
    if (img == NULL)
    {
        exit(1);
    }
    img->nLigne = img->nLigne;
    img->nColonne = img->nColonne;
    int n = 0, i = 0;
    for (i = 0; i < len; i++)
        if (n < hist[i])
            n = hist[i];

    const int ecart_x = 2, esp_haut = 50, esp_gauche = 50, esp_bas = 50, esp_droite = 50, longeur = 200;
    img->nLigne = esp_haut + esp_bas + longeur;
    img->nColonne = esp_gauche + esp_droite + (len + 2) * ecart_x;

    img->r = matrice_hist(n, hist, len, ecart_x, esp_haut, esp_gauche, esp_bas, esp_droite, longeur, 0, 72);
    img->g = matrice_hist(n, hist, len, ecart_x, esp_haut, esp_gauche, esp_bas, esp_droite, longeur, 0, 214);
    img->b = matrice_hist(n, hist, len, ecart_x, esp_haut, esp_gauche, esp_bas, esp_droite, longeur, 0, 214);
    return img;
}
ImageC *profilGC(int *prof, int len)
{
    ImageC *img = malloc(sizeof(ImageC));
    if (img == NULL)
    {
        exit(1);
    }
    img->nLigne = img->nLigne;
    img->nColonne = img->nColonne;
    int n = 0, i = 0;
    for (i = 0; i < len; i++)
        if (n < prof[i])
            n = prof[i];

    const int ecart_x = 3, esp_haut = 50, esp_gauche = 50, esp_bas = 50, esp_droite = 50, longeur = 120;
    img->nLigne = esp_haut + esp_bas + longeur;
    img->nColonne = esp_gauche + esp_droite + (len + 2) * ecart_x;

    img->r = matrice_profil(n, prof, len, ecart_x, esp_haut, esp_gauche, esp_bas, esp_droite, longeur, 0, 37);
    img->g = matrice_profil(n, prof, len, ecart_x, esp_haut, esp_gauche, esp_bas, esp_droite, longeur, 0, 116);
    img->b = matrice_profil(n, prof, len, ecart_x, esp_haut, esp_gauche, esp_bas, esp_droite, longeur, 0, 116);
    return img;
}
ImageG *interpolation_knnG(ImageG *img, int k)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne * k;
    r->nColonne = img->nColonne * k;
    r->data = interpolation_knn(img->data, img->nLigne, img->nColonne, k, k);
    return r;
}
ImageG *interpolation_bilG(ImageG *img)
{
    ImageG *r = malloc(sizeof(ImageG));
    if (r == NULL)
    {
        exit(1);
    }
    r->nLigne = img->nLigne * 2 - 1;
    r->nColonne = img->nColonne * 2 - 1;
    r->data = interpolation_bilineaire(img->data, img->nLigne, img->nColonne);
    return r;
}