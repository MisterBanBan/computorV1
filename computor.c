#include "computor.h"
#include "libft/inc/libft.h"

int main(int argc, char **argv)
{
    t_equation *equation;
    if(argc != 2)
    {
        printf("Error: Invalid number of arguments\n"
            "for example: ./computor \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"");
        return (1);
    }
    else
    {
        equation = ft_calloc(1, sizeof(t_equation));
        if(!equation)
            return (1);
        if (parse_equation(argv[1], equation) == 1)
        {
            printf("error");
            free(equation);
            return (1);
        }
    }
    free(equation);
    return (0);
}

int get_degre(t_equation *equation)
{
    if (equation->degre > 2)
        return (0);
    if (equation->a != 0)
        equation->degre = 2;
    else if (equation->b != 0)
        equation->degre = 1;
    else
        equation->degre = 0;
    return (0);
}

int parse_equation(char *input_user, t_equation *equation)
{
    char *left_side;
    char *right_side;
    char *eq;
    int sign;
    double coeff;
    int exp;
    int n_move;
    char *p;
    char *q;
    
    eq = strchr(input_user, '=');
    if(!eq)
        return (0);
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
    while(*p)
    {
        n_move = 0;
        sign = 1;
        while(*p && *p == ' ')
            p++;
        if (*p == '-')
        {
            sign = -1;
            p++;
        }
        else if (*p == '+')
        {
            sign = 1;
            p++;
        }
        if (parse_format(p, &coeff, &exp, &n_move) == 0)
        {
            free(left_side);
            free(right_side);
            return 1;
        }
        p += n_move;
        double result_final_coeff = coeff * sign;
        if (fill_tab(equation, result_final_coeff, exp) == 1)
        {
            free(left_side);
            free(right_side);
            return 1;
        }

    }
    while(*q)
    {
        n_move = 0;
        sign = 1;
        while(*q && *q == ' ')
            q++;
        if (*q == '-')
        {
            sign = -1;
            q++;
        }
        else if (*q == '+')
        {
            sign = 1;
            q++;
        }
        if (parse_format(q, &coeff, &exp, &n_move) == 0)
        {
            free(left_side);
            free(right_side);
            return 1;
        }
        q += n_move;
        double result_final_coeff = coeff * sign * (-1);
        if (fill_tab(equation, result_final_coeff, exp) == 1)
        {
            free(left_side);
            free(right_side);
            return 1;
        }
    }
    free(left_side);
    free(right_side);
    return (0);
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
        equation->degre = exp;
    else
    {
        printf("Its a rong exp");
        return (1);
    }
    return (0);

}