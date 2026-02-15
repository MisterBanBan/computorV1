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
void get_degre(t_equation *equation);
int parsing_equation(t_equation *equation, char *equation_side, int side_sign);
void print_equation(t_equation *equation);
void resolver(t_equation *equation);