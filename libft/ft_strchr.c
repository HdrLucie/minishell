/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:18:00 by ehautefa          #+#    #+#             */
/*   Updated: 2020/12/06 12:48:19 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	car;
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	car = (char)c;
	while (str[i])
	{
		if (str[i] == car)
			return (&str[i]);
		i++;
	}
	if (car == '\0')
		return (&str[i]);
	return (0);
}
