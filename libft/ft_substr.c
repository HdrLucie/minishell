/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:19:28 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/08 08:40:11 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_substr(const char *s, int start, size_t len)
{
	char		*str;
	size_t		i;

	i = 0;
	str = ft_strnew(len);
	if ((size_t)start >= ft_strlen(s))
		return (str);
	if (str == NULL)
		return (NULL);
	while (i < len && s && s[i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

