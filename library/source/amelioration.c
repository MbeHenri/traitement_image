#include <stdio.h>
#include <stdlib.h>
#include "../entete/Image.h"

ImageG *transform_linear(ImageG *img);
ImageG *transform_linear_satur(ImageG *img);
ImageG *transform_linear_morceau(ImageG *img);
ImageG *transform_not_linear(ImageG *img);
ImageG *egalizer_hist(ImageG *img, char type);
ImageG *egalizer_hist_local(ImageG *img, int pasVoisin);