#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "library/entete/Image.h"
#include "library/entete/base.h"

int main(int argc, char const *argv[])
{

    FILE* f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }
    
    char ch[5];
    fscanf(f, "%s\n", ch);
    
    if( strcmp(ch, "P1") == 0){
        printf("> Image binaire \n");
        ImageB * img = read_B(f);
        fclose(f);
        
        ImageG* r = grisB(img);
        free_ImageB(img);
        
        char* dest = (char*) malloc((1+strlen(argv[1]))* sizeof(char));
        dest[0]='\0';
        strcat(dest,argv[1]);
        strcat(dest,".pgm");
        
        write_G(r, dest);
        free_ImageG(r);
        
    }else if (strcmp(ch, "P2") == 0)
    {
        printf("> Image a niveau de gris \n");
        ImageG * img = read_G(f);
        fclose(f);
        
        int ** d = difference(img->data, img->nLigne, img->nColonne, 255);
        free_matrix(img->data, img->nLigne);
        img->data = d ;
        
        char* dest = (char*) malloc((1+strlen(argv[1]))* sizeof(char));
        dest[0]='\0';
        strcat(dest,argv[1]);
        strcat(dest,".pgm");
        
        write_G(img, dest);
        free_ImageG(img);
        
    }else if( strcmp(ch, "P3") == 0){
        printf("> Image a couleur \n");
        fclose(f);
    }else{
        printf("[ format de fichier non pris en charge ]\n");
        fclose(f);
        exit(1);
    }
    
    return 0;
}