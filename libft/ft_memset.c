/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:17:30 by ehautefa          #+#    #+#             */
/*   Updated: 2020/12/20 14:01:26 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)b;
	while (i < (int)len)
	{
		tmp[i] = (char)c;
		i++;
	}
	return (b);
}
