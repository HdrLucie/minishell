/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:18:29 by ehautefa          #+#    #+#             */
/*   Updated: 2020/12/06 12:43:21 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	size_dst;
	unsigned int	size_src;

	i = 0;
	size_dst = ft_strlen(dst);
	size_src = ft_strlen(src);
	if (dstsize == 0)
		return (size_src);
	while (src && dst && src[i] != 0 && i + size_dst < dstsize - 1)
	{
		dst[size_dst + i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[size_dst + i] = '\0';
	if (size_dst > dstsize)
		return (size_src + dstsize);
	else
		return (size_src + size_dst);
}
