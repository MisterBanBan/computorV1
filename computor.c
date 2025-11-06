#include <stdlib.h>
#include <stdio.h>
#include "computor.h"
#include <math.h>
#include <string.h>

int main (int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s \"equation\"\n", argv[0]);
        return 1;
    }

}

void parse_equation(const char *input, t_equation *equation) {

    equation->a = 0;
    equation->b = 0;
    equation->c = 0;
    equation->degree = 0;

}

void resolve_degree_zero(t_equation *equation) {
    printf("Polynomial degree: 0\n");
    if (equation->c == 0)
        printf("Any real number is a solution.\n");
    else
        printf("No solution.\n");
}

void resolve_degree_one(t_equation *equation) {
    //bx + c = 0
    double delta;
    delta = -equation->c / equation->b;
    printf("This solution at x = -%f / %f is x = %f",equation->c, equation->b, delta);
}

void resolve_degree_two(t_equation *equation) {
    //b^2 - 4ac
    double delta;
    delta = 0;

    delta = equation->b * equation->b - 4 * equation->a * equation->c;
    if (delta > 0) {
        
    } else if (delta == 0) {

    }
    else {

    }

}

void resolve_equation(t_equation *equation) {
    if (equation->degree > 2)
        printf("The polynomial degree is strictly greater than 2, I can't solve.");
    else if(equation->degree == 2)
        resolve_degree_two(equation);
    else if(equation->degree == 1)
        resolve_degree_one(equation);
    else if(equation->degree == 0)
        resolve_degree_zero(equation);
    else
        printf("is negatif cant resolve");
}