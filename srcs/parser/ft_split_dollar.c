/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:56:50 by elise             #+#    #+#             */
/*   Updated: 2021/10/18 15:14:47 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	count_word(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 1;
	if(str[i] == '$')
		word = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			word++;
			while (str && str[i] && str[i] != ' ' && str[i] != '$')
				i++;
		}
		i++;
	}
	return (word);
}

static int	size_word(char *str, int k)
{
	int	size;

	size = k;
	if (str[k] == '$')
		while (str && str[++k] && str[k] != ' ' && str[k] != '$')
			;
	else
		while (str && str[k] && str[k] != '$')
			k++;
	size = k - size;
	return (size);
}

static int fill_strs(char *str, char **strs, int word)
{
	int	i;
	int	j;
	int	k;
	int	size;

	j = 0;
	k = 0;
	while (j < word)
	{
		size = size_word(str, k);
		strs[j] = malloc((size + 1) * sizeof(**strs));
		if (strs[j] == NULL)
			return (print_error("ALLOCATION FAILED\n", -1));
		i = 0;
		while (i < size)
		{
			strs[j][i] = str[k];
			k++;
			i++;
		}
		strs[j][i] = '\0';
		j++;
	}
	strs[j] = NULL;
	return (0);
}

char	**ft_split_dollar(char *str)
{
	char	**strs;
	int		word;

	word = count_word(str);
	strs = malloc((word + 1) * sizeof(*strs));
	if (strs == NULL)
		return (NULL);
	if (fill_strs(str, strs, word) == -1)
		return (NULL);
	return (strs);
}