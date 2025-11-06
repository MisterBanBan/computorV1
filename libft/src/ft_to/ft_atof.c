/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtbanban <mtbanban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:58:33 by mtbanban          #+#    #+#             */
/*   Updated: 2025/11/06 11:04:34 by mtbanban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double ft_atof(const char *str)
{
    double result;
    double decimal;
    int i;
    int sign;
    
    decimal = 0.0;
    result = 0.0;
    i = 0;
    sign = 1;

    while (str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == ' ')
		i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    
    while (ft_isdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
    {
        i++;
        double factor = 0.1;
        while (ft_isdigit(str[i]))
        {
            decimal += (str[i] - '0') * factor;
            factor *= 0.1;
            i++;
        }
    }
    return (sign * (result + decimal));
}