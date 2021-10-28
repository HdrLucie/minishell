/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:56:50 by elise             #+#    #+#             */
/*   Updated: 2021/10/28 15:51:24 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var(int i, int *word, char *str)
{
	*word = *word + 1;
	i++;
	if (str[i] && str[i] == '{')
	{
		while (str && str[i] && str[i] != '}')
			i++;
		i++;
	}
	else
		while (str && str[i] && isnt_var(str, &i))
			i++;
	if (str && str[i] != '\0')
		*word = *word + 1;
	return (i);
}

static int	count_word(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 1;
	if (str[i] == '$')
		word = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
			while (str && str[++i] && str[i] != '\'')
				;
		if (str[i] == '$')
			i = find_var(i, &word, str);
		else
			i++;
	}
	return (word);
}

static int	size_word(char *str, int k)
{
	int	size;

	size = k;
	if (str[k] == '$' && str[k + 1] && str[k + 1] == '{')
	{
		while (str && str[++k] && str[k] != '}')
			;
		k++;
	}
	else if (str[k] == '$')
		while (str && str[++k] && isnt_var(str, &k))
			;
	else
	{
		while (str && str[k] && str[k] != '$')
		{
			if (str[k] == '\'')
			{
				while (str && str[++k] && str[k] != '\'')
					;
			}
			k++;
		}
	}
	size = k - size;
	return (size);
}

static int	fill_strs(char *str, char **strs, int word)
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
