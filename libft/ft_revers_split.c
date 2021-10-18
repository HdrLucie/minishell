/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revers_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:57:58 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/18 15:29:23 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	find_size_total(char **strs)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (strs && strs[i])
	{
		res += ft_strlen(strs[i]);
		i++;
	}
	res += i - 1;
	if (res < 0)
		return (0);
	return (res);
}

static void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	*ft_reverse_split(char **strs, char sep)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	*str;

	i = 0;
	k = 0;
	size = find_size_total(strs);
	str = malloc((size + 1) * sizeof(*str));
	if (str == NULL)
		return (NULL);
	while (strs && strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			str[k] = strs[i][j];
			k++;
			j++;
		}
		str[k++] = sep;
		i++;
	}
	free_strs(strs);
	str[k++] = '\0';
	printf("str = |%s|\n", str);
	return (str);
}