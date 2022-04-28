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
        
        fclose(f);
    }else if (strcmp(ch, "P2") == 0)
    {
        printf("> Image a niveau de gris \n");
        ImageG * img = read_G(f);
        fclose(f);
        
        ImageG* r = inverseG(img);
        free_ImageG(img);
        
        // on contruit l'image destination
        char* dest = (char*) malloc((1+strlen(argv[1]))* sizeof(char));
        dest[0]='\0';
        strcat(dest,argv[2]);
        strcat(dest,".pgm");
        
        write_G(r,dest);
        free_ImageG(r);
    
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
