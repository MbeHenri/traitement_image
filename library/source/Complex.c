#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../entete/Complex.h"

Complex new_complex(double rez, double img)
{
    Complex c = malloc(sizeof(Complex));
    if (c != NULL)
    {
        c->rez = rez;
        c->img = img;
    }
    return c;
}
void free_complex(Complex c)
{
    free(c);
}
void copie_complex(Complex c, Complex copie)
{
    if (copie != NULL && c != NULL)
    {
        copie->rez = c->rez;
        copie->img = c->img;
    }
}
void plus_complex(Complex c1, Complex c2, Complex r)
{
    if (r != NULL && c1 != NULL && c2 != NULL)
    {
        r->rez = c1->rez + c2->rez;
        r->img = c1->img + c2->img;
    }
}
void moins_complex(Complex c1, Complex c2, Complex r)
{
    if (r != NULL && c1 != NULL && c2 != NULL)
    {
        r->rez = c1->rez - c2->rez;
        r->img = c1->img - c2->img;
    }
}
void fois_complex(Complex c1, Complex c2, Complex r)
{
    if (r != NULL && c1 != NULL && c2 != NULL)
    {
        r->rez = c1->rez * c2->rez - c1->img * c2->img;
        r->img = c1->img * c2->rez + c2->img * c1->rez;
    }
}
void fois_complex_ratio(Complex c, double k ,Complex r)
{
    if (r != NULL && c != NULL)
    {
        r->rez = c->rez * k;
        r->img = c->img * k;
    }
}
Complex *new_tab_complex(int nbre)
{
    Complex *new_tab = malloc(nbre * sizeof(Complex));
    if (new_tab != NULL)
    {
        int i = 0;
        for (i = 0; i < nbre; i++)
            new_tab[i] = new_complex(0, 0);
    }
    return new_tab;
}
void free_tab_complex(Complex *tab, int nbre)
{
    if (tab != NULL)
    {
        int i = 0;
        for (i = 0; i < nbre; i++)
            free_complex(tab[i]);

        free(tab);
    }
}
Complex **new_matrix_complex(int nLigne, int nCol)
{
    Complex **new_matrix = malloc(nLigne * sizeof(Complex *));
    if (new_matrix != NULL)
    {
        int i = 0;
        for (i = 0; i < nLigne; i++)
            new_matrix[i] = new_tab_complex(nCol);
    }
    return new_matrix;
}
void free_matrix_complex(Complex **matrix, int nLigne, int nCol)
{
    if (matrix != NULL)
    {
        int i = 0;
        for (i = 0; i < nLigne; i++)
            free_tab_complex(matrix[i], nCol);
        free(matrix);
    }
}
char *complex_to_string(Complex c)
{
    char *ch = NULL;
    if (c != NULL)
    {
        char *ch_rez = NULL;
        char *ch_img = NULL;
        if (c->rez != 0)
        {
            ch_rez = malloc(MAX_LENGH_REZ * sizeof(char));
            sprintf(ch_rez, "%lf", c->rez);
        }
        if (c->img != 0)
        {
            ch_img = malloc(MAX_LENGH_IMG * sizeof(char));
            sprintf(ch_img, "%lf", c->img);
        }
        
        if (ch_rez == NULL && ch_img == NULL)
        {
            ch = malloc(4 * sizeof(char));
            strcat(ch, "0");
        }
        else if (ch_rez == NULL && ch_img != NULL)
        {
            ch = malloc((2 + strlen(ch_img)) * sizeof(char));
            strcat(ch, ch_img);
            strcat(ch, "*i");
            free(ch_img);
        }
        if (ch_rez != NULL && ch_img == NULL)
        {
            ch = malloc(strlen(ch_rez) * sizeof(char));
            strcat(ch, ch_rez);
            free(ch_rez);
        }
        if (ch_rez != NULL && ch_img != NULL)
        {
            ch = malloc((7 + strlen(ch_img)) * sizeof(char));
            strcat(ch, ch_rez);
            if (c->img > 0)
                strcat(ch, " + ");
            strcat(ch, ch_img);
            strcat(ch, "*i");
            free(ch_img);
            free(ch_rez);
        }
    }
    return ch;
}
Complex* convert_tab_int_to_complex(int * v, int n){
    Complex* tab = new_tab_complex(n);
    int i=0;
    for (i = 0; i < n; i++)
        tab[i]->rez = v[i];
    return tab;
}
Complex** convert_matrix_int_to_complex(int ** v, int nLigne, int nCol){
    Complex** tab = new_matrix_complex(nLigne,nCol);
    int i=0,j=0;
    for (i = 0; i < nLigne; i++)
        for (j = 0; j < nLigne; j++)
            tab[i][j]->rez = v[i][j];
    return tab;
}
double norme_complex(Complex c){
    return sqrt(c->rez*c->rez+c->img*c->img);
}
double arg_complex(Complex c){
    double angle=__DBL_MAX__;
    if (c->rez == 0 && c->img != 0)
    {
        if (c->img > 0)
            angle= M_PI_2;
        else
            angle= -M_PI_2;
    }else if(c->rez != 0 && c->img == 0)
    {
        if (c->rez > 0)
            angle= 0;
        else
            angle= M_PI;
    }else if (c->rez != 0 && c->img != 0){
        angle = atan(c->img/c->rez);
        if (c->img < 0)
            angle+=M_PI;
        
    }
    return angle;
}