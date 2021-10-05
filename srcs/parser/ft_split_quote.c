/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:16:19 by ehautefa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/04 11:25:21 by ehautefa         ###   ########.fr       */
=======
/*   Updated: 2021/10/05 09:01:43 by ehautefa         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i], str[i - 1]))
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
	while (str[i] && is_space(str[i], str[i - 1]))
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
<<<<<<< HEAD
		printf("Size word : %d\n", size);
=======
>>>>>>> main
		split[j] = malloc((size + 1) * sizeof(**split));
		if (split[j] == NULL)
			return (NULL);
		while (++i < size)
			split[j][i] = str[k++];
		split[j][i] = '\0';
<<<<<<< HEAD
		k++;
=======
>>>>>>> main
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
