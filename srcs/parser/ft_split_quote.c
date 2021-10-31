/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:16:19 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/31 13:48:34 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_token(char *str, int i, char end)
{
	i = i + 1;
	while (str[i] && str[i] != end)
		i++;
	if (str[i] != end && end != '\n')
		return (print_error("UNCLOSED QUOTE\n", -1, 130));
	i++;
	return (i);
}

int	count_word(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
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
	while (str[i] && is_space(str[i]))
		i++;
	begin = i;
	*k = *k + begin;
	i = check_quote(str, i);
	return (i - begin);
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
		if (str && str[k] && str[k + 1] && (str[k] == '\"' || str[k] == '\''))
			k++;
		split[j][i] = '\0';
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split_quote(char *str)
{
	int		word;
	char	**split;

	if (str == NULL)
		return (print_char_error("ALLOCATION FAILED\n", -1, -1));
	word = count_word(str);
	if (word == -1)
		return (NULL);
	split = malloc((word + 1) * sizeof(*split));
	if (split == NULL)
		print_char_error("ALLOCATION FAILED\n", -1, -1);
	split = fill_split(str, split, word);
	if (split == NULL)
		return (NULL);
	split = remove_comments(split);
	free(str);
	return (split);
}
