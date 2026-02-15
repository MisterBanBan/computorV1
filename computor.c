#include "computor.h"
#include <math.h>
#include "libft/inc/libft.h"
#include "libft/inc/get_next_line.h"

int main(int argc, char **argv)
{
    t_equation *equation;
    char       *input;
    size_t     len;

    if (argc > 2)
    {
        printf("Error: Invalid number of arguments\n");
        return (1);
    }
    if (argc == 1)
    {
        input = get_next_line(0);
        if (!input)
            return (1);
        len = ft_strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = '\0';
    }
    else
        input = argv[1];
    equation = ft_calloc(1, sizeof(t_equation));
    if (!equation)
    {
        if (argc == 1)
            free(input);
        return (1);
    }
    if (parse_equation(input, equation) == 1)
    {
        printf("error\n");
        free(equation);
        if (argc == 1)
            free(input);
        return (1);
    }
    get_degre(equation);
    print_equation(equation);
    resolver(equation);
    free(equation);
    if (argc == 1)
        free(input);
    return (0);
}

double ft_sqrt(double x)
{
    double t;
    double prev;

    if (x < 0)
        return 0;
    if (x == 0)
        return 0;
    t = x;
    prev = 0;
    while(prev != t)
    {
        prev = t;
        t = (t + x / t) / 2.0;
    }
    return (t);
}

void print_equation(t_equation *equation)
{
    printf("Reduced form: %lf * X^0",equation->c);
    if(equation->b >= 0)
        printf(" + %lf * X^1", equation->b);
    else
        printf(" - %lf * X^1", equation->b * -1);
    if(equation->a >= 0)
        printf(" + %lf * X^2 = 0\n", equation->a);
    else
        printf(" - %lf * X^2 = 0\n", equation->a * -1);
    printf("Polynomial degree: %d\n", equation->degre);
}

void degre_zero(t_equation *equation)
{
    if(equation->c == 0)
        printf("Any real number is a solution.\n");
    else
        printf("No solution.\n");
}

void degre_one(t_equation *equation)
{
    double result;

    result = (-equation->c) / (equation->b);
    printf("The solution is:\n%lf\n", result);
}

void degre_two(t_equation *equation)
{
    double delta;
    double x1;
    double x2;
    double real;
    double img;

    delta = (equation->b * equation->b) - (4 * equation->a * equation->c);
    if (delta > 0)
    {
        printf("Discriminant is strictly positive, the two solutions are:\n");
        x1 = (-equation->b + ft_sqrt(delta)) / (2 * equation->a);
        x2 = (-equation->b - ft_sqrt(delta)) / (2 * equation->a);
        printf("%lf\n%lf\n", x1, x2);
    }
    else if(delta == 0)
    {
        x1 = (-equation->b) / (2 * equation->a);
        printf("Discriminant is zero, the solution is:\n%lf\n", x1);
    }
    else if(delta < 0)
    {
        printf("Discriminant is strictly negative, the two complex solutions are:\n");
        
        real = -equation->b / (2 * equation->a);
        img = ft_sqrt(-delta) / (2 * equation->a);
        printf("%lf + %lfi\n",real, img);
        printf("%lf - %lfi\n",real, img);
        
    }
}

void resolver(t_equation *equation)
{
    if(equation->degre == 0)
    {
        degre_zero(equation);
    }
    else if(equation->degre == 1)
    {
        degre_one(equation);
    }
    else if (equation->degre == 2) 
    {
        degre_two(equation);
    }
    else
    {
        printf("The polynomial degree is strictly greater than 2, I can't solve.\n");
    }
}

void get_degre(t_equation *equation)
{
    if (equation->a != 0)
        equation->degre = 2;
    else if (equation->b != 0)
        equation->degre = 1;
    else
        equation->degre = 0;
}

int parse_equation(char *input_user, t_equation *equation)
{
    char *left_side;
    char *right_side;
    char *eq;
    char *p;
    char *q;
    
    eq = strchr(input_user, '=');
    if(!eq)
        return (1);
    left_side = ft_substr(input_user, 0, (size_t)(eq - input_user)); //input_user start at 0 is a pointeur and eq start at = is a pointeur
    if (!left_side)
        return (1);
    right_side = ft_substr(input_user,(size_t)(eq - input_user + 1), ft_strlen(eq + 1));
    if (!right_side)
    {
        free(left_side);
        return (1);
    }
    p = left_side;
    q = right_side;
    if(parsing_equation(equation, p, 1) == 1)
    {
        free(left_side);
        free(right_side);
        return 1;
    }
    if(parsing_equation(equation, q, -1) == 1)
    {
        free(left_side);
        free(right_side);
        return 1;
    }
    free(left_side);
    free(right_side);
    return (0);
}

int parsing_equation(t_equation *equation, char *equation_side, int side_sign)
{
    int sign;
    int n_move;
    double coeff;
    int exp;

    while(*equation_side)
    {
        n_move = 0;
        sign = 1;
        while(*equation_side && *equation_side == ' ')
            equation_side++;
        if (*equation_side == '-')
        {
            sign = -1;
            equation_side++;
        }
        else if (*equation_side == '+')
        {
            sign = 1;
            equation_side++;
        }
        if (parse_format(equation_side, &coeff, &exp, &n_move) == 1)
            return 1;
        if (n_move <= 0)
            return (1);
        equation_side += n_move;
        double result_final_coeff = coeff * sign * side_sign;
        if (fill_tab(equation, result_final_coeff, exp) == 1)
            return 1;
    }
    return 0;
}

int parse_format(char *input_user, double *coeff, int *exp, int *n_move)
{
    int i;
    i = 0;

    i = sscanf(input_user, " %lf * X^%d %n", coeff, exp, n_move);
    if (i == 2)
        return (0);
    return (1);
}

int fill_tab(t_equation *equation, double coeff, int exp)
{
    if (exp == 0)
        equation->c += coeff;
    else if(exp == 1)
        equation->b += coeff;
    else if(exp == 2)
        equation->a += coeff;
    else if(exp > 2)
    {
        if (exp > equation->degre)
            equation->degre = exp;
    }
    else
    {
        printf("Its a rong exp");
        return (1);
    }
    return (0);

}