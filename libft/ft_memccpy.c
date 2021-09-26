/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:17:04 by ehautefa          #+#    #+#             */
/*   Updated: 2020/09/16 09:17:05 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int		i;
	char	*dest;
	char	*sorc;

	i = 0;
	dest = (char *)dst;
	sorc = (char *)src;
	while (i < (int)n)
	{
		dest[i] = sorc[i];
		if ((unsigned char)dest[i] == (unsigned char)c)
			return (&dest[i + 1]);
		i++;
	}
	if (n > ft_strlen(dest))
		dest[i] = '\0';
	return (NULL);
}
