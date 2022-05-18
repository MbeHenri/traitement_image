#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // on contruit l'image destination
    char *dest = (char *)malloc((1 + strlen(argv[1])) * sizeof(char));
    dest[0] = '\0';
    strcat(dest, argv[1]);
    strcat(dest, ".pbm");

    FILE *f = fopen(dest, "w");
    if (f == NULL)
    {
        printf("[ il n'est pas possible d'ouvrir le fichier ]\n");
        exit(1);
    }

    if (argv[2] == NULL || argv[3] == NULL)
    {
        exit(1);
    }
    char c = '0';
    if (argv[4] != NULL)
    {
        if (strcmp(argv[4], "noir") == 0)
        {
            c = '1';
        }
        else if (strcmp(argv[4], "blanc") == 0)
        {
            c = '0';
        }
    }
    fprintf(f, "P1\n");
    fprintf(f, "# realisation de Mbe\n");
    int i, j, nligne = atoi(argv[2]), ncol = atoi(argv[3]);
    fprintf(f, "%d %d\n", nligne, ncol);
    for (i = 0; i < nligne; i++)
    {
        for (j = 0; j < ncol; j++)
        {
            fprintf(f, "%c", c);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return 0;
}
