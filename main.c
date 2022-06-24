#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "library/entete/Complex.h"

int main()
{
    Complex *tab = new_tab_complex(2);
    tab[0]->img = -1;
    tab[1]->rez = 1;
    int i = 0;

    char *ch = NULL;
    for (i = 0; i < 2; i++)
    {
        ch = complex_to_string(tab[i]);
        printf("%s, |z|= %lf, arg(z)=%lf\n", ch, norme_complex(tab[i]), arg_complex(tab[i]));
        free(ch);
    }
    plus_complex(tab[0], tab[1], tab[1]);
    for (i = 0; i < 2; i++)
    {
        ch = complex_to_string(tab[i]);
        printf("%s, |z|= %lf, arg(z)=%lf\n", ch, norme_complex(tab[i]), arg_complex(tab[i]));
        free(ch);
    }
    return 0;
}