#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../library/entete/Image.h"

int main(int argc, char const *argv[])
{
    FILE* f = fopen(argv[1], "r");
    if (f == NULL){
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }
    
    char ch[5];
    fscanf(f, "%s\n", ch);
    
    if( strcmp(ch, "P1") == 0){
        printf("> Image binaire \n");
        printf("[ rien a faire ]\n");
        fclose(f);
    }else if (strcmp(ch, "P2") == 0)
    {
        printf("> Image a niveau de gris \n");
        ImageG * img = read_G(f);
        fclose(f);
        int max = max_G(img), min = min_G(img);
        double seuil = (max - min)/2;
        ImageB* r = binarisationG(img, seuil);
        
        free_ImageG(img);
        
        // on contruit l'image destination
        char* dest = (char*) malloc((1+strlen(argv[1]))* sizeof(char));
        dest[0]='\0';
        strcat(dest,argv[1]);
        strcat(dest,".pbm");
        
        write_B(r,dest);
        
        free_ImageB(r);
    
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
