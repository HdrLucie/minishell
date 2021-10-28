/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revers_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:57:58 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 15:52:09 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (res);
}

char	*fill_str(char **strs, char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (strs && strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			str[k] = strs[i][j];
			k++;
			j++;
		}
		i++;
	}
	free_strs(strs);
	str[k] = '\0';
	return (str);
}

char	*ft_reverse_split(char **strs)
{
	int		size;
	char	*str;

	size = find_size_total(strs);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str = fill_str(strs, str);
	return (str);
}
