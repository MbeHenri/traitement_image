#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED
#define MAX_LENGH_REZ 1400
#define MAX_LENGH_IMG 1400

typedef struct Complexe* Complex;
struct Complexe
{
    double rez;
    double img;
};

Complex new_complex(double rez, double img);
void free_complex(Complex c);
void copie_complex(Complex c, Complex copie);
void plus_complex(Complex c1, Complex c2, Complex r);
void moins_complex(Complex c1, Complex c2, Complex r);
void fois_complex(Complex c1, Complex c2, Complex r);
void fois_complex_ratio(Complex c, double k ,Complex r);
Complex *new_tab_complex(int nbre);
void free_tab_complex(Complex *tab, int nbre);
Complex **new_matrix_complex(int nLigne, int nCol);
void free_matrix_complex(Complex **matrix, int nLigne, int nCol);
char *complex_to_string(Complex c);
Complex* convert_tab_int_to_complex(int * v, int n);
Complex** convert_matrix_int_to_complex(int ** v, int nLigne, int nCol);
double norme_complex(Complex c);
double arg_complex(Complex c);
#endif