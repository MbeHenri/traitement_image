#ifndef INTERPOLATION_H_INCLUDED
#define INTERPOLATION_H_INCLUDED
#include "Image.h"

/*
    interpolation d'images (changement d'echelle)
*/
//pour les images a couleur de gris et binaire
ImageGB* ibterpolation_knn(ImageGB* img, int k);
ImageGB* ibterpolation_bilineaire(ImageGB* img);
ImageGB* ibterpolation_bicubique(ImageGB* img);

#endif // INTERPOLATION_H_INCLUDED