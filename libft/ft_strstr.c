/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:19:05 by ehautefa          #+#    #+#             */
/*   Updated: 2021/01/21 11:51:31 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	str = (char *)haystack;
	if (needle[i] == '\0')
		return (str);
	while (str[i])
	{
		k = i;
		j = 0;
		while (haystack[k] == needle[j])
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
