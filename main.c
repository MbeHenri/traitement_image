#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "library/entete/Image.h"

int main()
{

    printf("hello\n");
    int * h =malloc(256*sizeof(int));
    
    int i =0;
    for ( i = 0; i < 256; i++)
    {
        h[i] = 2*i;
    }
    
    ImageC* img = histogrameC(h,256);
    
    write_C(img,"hist.ppm");
    return 0;
}