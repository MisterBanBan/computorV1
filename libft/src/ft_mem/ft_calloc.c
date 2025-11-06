/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtbanban <mtbanban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:15:08 by afavier           #+#    #+#             */
/*   Updated: 2025/11/05 21:55:07 by mtbanban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	char	*tab;
	size_t	sz;
	size_t	i;

	i = 0;
	sz = number * size;
	if (size != 0 && sz / size != number)
		return (NULL);
	tab = malloc(sz);
	if (!tab)
		return (NULL);
	while (i < sz)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}
