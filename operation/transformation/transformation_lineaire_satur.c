#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../library/entete/Image.h"

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
        
        int s_min = atoi(argv[2]), s_max=atoi(argv[3]);
        if(s_min == s_max){
            printf("[ donner des elements de saturation differents ]\n");
            exit(1);
        }
        if (s_min > s_max)
        {
            int aux = s_max;
            s_max = s_min;
            s_min = aux;
        }
        
        printf("0/100\n");
        ImageG* r = transform_lineaire_satur_G(img,s_min, s_max);
        printf("100/100\n");
    
        char * dest = (char *)malloc((18 + strlen(argv[1])) * sizeof(char));
        dest[0] = '\0';
        strcat(dest, argv[1]);
        strcat(dest, "_transform_ls.pgm");
        
        write_G(r, dest);
        free_ImageG(r);
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
