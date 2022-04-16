#ifndef AMELIORATION_H_INCLUDED
#define AMELIORATION_H_INCLUDED
#include "Image.h"

/*
    Amelioration d'images
*/
//pour les images a couleur de gris
ImageG* transform_linear(ImageG* img);
ImageG* transform_linear_satur(ImageG* img);
ImageG* transform_linear_morceau(ImageG* img);
ImageG* transform_not_linear(ImageG* img);
ImageG* egalizer_hist(ImageG* img, char type);
ImageG* egalizer_hist_local(ImageG* img, int pasVoisin);


#endif // AMELIORATION_H_INCLUDED