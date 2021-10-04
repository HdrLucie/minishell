/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:16:19 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/04 09:17:13 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_token(char *str, int *i, char end)
{
	*i = *i + 1;
	if (end == '\"')
		while (str[*i] && (str[*i] != end || str[*i - 1] == '\\'))
			*i = *i + 1;
	else
		while (str[*i] && str[*i] != end)
			*i = *i + 1;
	if (str[*i] != end)
		return (-1);
	*i = *i + 1;
	return (0);
}

int	check_quote(char *str, int i)
{
	if (!(str[i - 1] && str[i - 1] == '\\'))
	{
		if (str[i] == '\"' && find_token(str, &i, '\"') == -1)
			return (-1);
		else if (str[i] == '\'' && find_token(str, &i, '\'') == -1)
			return (-1);
		else if (str[i] == '#' && find_token(str, &i, '\n') == -1)
			return (i);
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '(' && 
			find_token(str, &i, ')') == -1)
			return (-1);
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '{' && 
			find_token(str, &i, '}') == -1)
			return (-1);
	}
	while (str[i] && !((str[i] >= '\t' && str[i] <= '\r')
			|| str[i] == ' ' || str[i] == '\"' || str[i] == '\''
			|| str[i] == '$' || str[i] == '#' || str[i] == '|'
			|| str[i] == '>' || str[i] == '<'))
		i++;
	return (++i);
}

int	count_word(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
			i++;
		if (str[i])
			word++;
		i = check_quote(str, i);
		if (i == -1)
			return (-1);
	}
	return (word);
}

int	size_word(char *str, int *k)
{
	int	i;
	int	begin;

	i = 0;
	while (str[i] && ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
		i++;
	begin = i;
	*k = *k + begin;
	i = check_quote(str, i);
	return (i - begin - 1);
}

char	**fill_split(char *str, char **split, int word)
{
	int		j;
	int		i;
	int		k;
	int		size;

	j = -1;
	k = 0;
	while (++j < word)
	{
		i = -1;
		size = size_word(&str[k], &k);
		split[j] = malloc((size + 1) * sizeof(**split));
		if (split[j] == NULL)
			return (NULL);
		while (++i < size)
			split[j][i] = str[k++];
		split[j][i] = '\0';
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split_quote(char *str)
{
	int		word;
	char	**split;

	word = count_word(str);
	if (word == -1)
		return (NULL);
	split = malloc((word + 1) * sizeof(*split));
	if (split == NULL)
	{
		errno = -1;
		return (NULL);
	}
	split = fill_split(str, split, word);
	if (split == NULL)
	{
		errno = -1;
		return (NULL);
	}
	return (split);
}
