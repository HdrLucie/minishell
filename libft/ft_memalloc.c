/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:17:01 by ehautefa          #+#    #+#             */
/*   Updated: 2021/08/23 14:41:30 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memalloc(size_t size)
{
	char	*a;
	int		i;

	i = 0;
	a = (char *)malloc(size);
	if (a == NULL)
		return (NULL);
	while (i < (int)size)
	{
		a[i] = 0;
		i++;
	}
	return ((void *)a);
}
