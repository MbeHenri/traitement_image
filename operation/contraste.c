#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../library/entete/Image.h"
/*
    OPTIONS :
        *  "-ecart_type" : variance a ecart type
        *  "-min_max" : varance a niveau de gris min - max
        
    NB: si on entre aucun de ces option alors on donnera les deux

*/
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
        
        fclose(f);
    }else if (strcmp(ch, "P2") == 0)
    {
        printf("> Image a niveau de gris \n");
        ImageG * img = read_G(f);
        double contraste_ecart_type = contraste_ecart_type_G(img);
        double contraste_min_max = contraste_min_max_G(img);
        fclose(f);
        free_ImageG(img);
        
        if( argv[2] == NULL ){
            printf("/* constraste a niveau de gris (ecart type) : %f\n/* constraste a niveau de gris (min-max) : %f\n",contraste_ecart_type, contraste_min_max);
        }else if( strcmp(argv[2], "-ecart_type") == 0){
            printf("/* constraste a niveau de gris (ecart type) : %f\n",contraste_ecart_type);
        }else if( strcmp(argv[2], "-min_max") == 0 )
        {
            printf("/* constraste a niveau de gris (min-max) : %f\n",contraste_min_max);
        }else{
            printf(" [ aucun choix existant ]\n! entrez soit :\n* '-ecart_type' pour la variance ecart-type \n* '-min_max' pour la variance a niveau de gris min - max \n");
            exit(1);
        }
    
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
