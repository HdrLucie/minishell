/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:19:26 by ehautefa          #+#    #+#             */
/*   Updated: 2021/08/23 14:32:05 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	space(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	size;
	int	j;

	i = 0;
	j = 1;
	size = ft_strlen(s1);
	while (space(s1[i], set) && s1[i])
		i++;
	while (space(s1[size - j], set) && s1[size - j])
		j++;
	if (i == size)
		return (ft_strnew(0));
	return (ft_substr(s1, i, size - i - j + 1));
}
