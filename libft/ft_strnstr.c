/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:18:57 by ehautefa          #+#    #+#             */
/*   Updated: 2020/09/16 09:18:58 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	str = (char *)haystack;
	i = 0;
	if (needle[i] == '\0')
		return (str);
	while (str[i] && i < (int)len)
	{
		k = i;
		j = 0;
		while (str[k] == needle[j] && k < (int)len)
		{
			if (needle[j + 1] == '\0')
				return (&str[i]);
			k++;
			j++;
		}
		i++;
	}
	return (0);
}
