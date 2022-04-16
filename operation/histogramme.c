#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../library/entete/Image.h"

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
        fclose(f);
        unsigned int* hist = histogram_G(img);
        free_ImageG(img);
    
        char* dest = (char*) malloc((6+strlen(argv[1]))* sizeof(char));
        dest[0]='\0';
        strcat(dest,"hist_");strcat(dest,argv[1]);strcat(dest,".txt");
        
        
        f = fopen(dest , "w");
        if (f == NULL)
            exit(1);
        int i=0;
        fprintf(f, "couleur,occurence\n");
        for ( i = 0; i < 256; i++)
            fprintf(f, "%d,%d\n", i, hist[i] );
        
        printf("// histogramme de %s est dans le fichier %s\n", argv[1], dest);
        fclose(f);
        
        
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