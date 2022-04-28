#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../library/entete/Image.h"

int main(int argc, char const *argv[])
{
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }

    char ch[5];
    fscanf(f, "%s\n", ch);

    if (strcmp(ch, "P1") != 0)
    {
        printf("[ la premiere image doit etre une image binaire ]\n");
        fclose(f);
        exit(1);
    }
    ImageB* img1 = read_B(f);
    fclose(f);
    
    f = fopen(argv[2], "r");
    if (f == NULL)
    {
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }

    fscanf(f, "%s\n", ch);
    if (strcmp(ch, "P1") == 0)
    {
        ImageB * img2 = read_B(f);
        fclose(f);
        
        char * dest = (char *)malloc((4 + strlen(argv[3])) * sizeof(char));
        dest[0] = '\0';
        strcat(dest, argv[3]);
        strcat(dest, "_.pbm");
        
        ImageB *r = etB(img1, img2);
        free_ImageB(img2);
        free_ImageB(img1);
        
        write_B(r, dest);
        
    }
    else if (strcmp(ch, "P2") == 0)
    {
        ImageG *img2 = read_G(f);
        fclose(f);
        
        char * dest = (char *)malloc((4 + strlen(argv[3])) * sizeof(char));
        dest[0] = '\0';
        strcat(dest, argv[3]);
        strcat(dest, "_.pgm");
        
        ImageG *r = etG(img1, img2);
        
        free_ImageG(img2);
        free_ImageB(img1);
        
        write_G(r, dest);
    }
    else if (strcmp(ch, "P3") == 0)
    {
        printf("[ rien a faire ]\n");
        fclose(f);
    }
    else
    {
        printf("[ format de fichier non pris en charge ]\n");
        free_ImageB(img1);
        fclose(f);
        exit(1);
    }
    return 0;
}
