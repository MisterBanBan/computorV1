
typedef struct s_equation {
    double a;
    double b;
    double c;
    int degree;
} t_equation;

void    parse_equation(const char *input, t_equation *equation);
void    resolve_degree_zero(t_equation *equation);
void    resolve_degree_one(t_equation *equation);
void    resolve_degree_two(t_equation *equation);
void    resolve_equation(t_equation *equation);

