#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_equation{
    double a; //x^2
    double b; //x^1
    double c; //x^0
    int degre;
} t_equation;

int parse_format(char *equation, double *coeff, int *exp, int *n_move);
int parse_equation(char *input_user, t_equation *equation);
int fill_tab(t_equation *equation, double coeff, int exp);