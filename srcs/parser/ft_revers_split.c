/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revers_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:57:58 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/21 13:33:07 by elise            ###   ########.fr       */
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
	res += i - 1;
	if (res < 0)
		return (0);
	return (res);
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
	str[k - 1] = '\0';
	return (str);
}