/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:19:03 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/08 08:47:47 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (word);
}

static int	ft_size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

int	ft_split2(int word, char c, char **strs, char *s)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = -1;
	while (++j < word)
	{
		while (s && s[i] && s[i] == c)
			i++;
		size = ft_size_word(s, c, i);
		strs[j] = ft_substr((char *)s, i, size);
		if (strs[j] == NULL)
		{
			ft_free(strs, j);
			return (-1);
		}
		i += size;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**strs;
	int		j;

	word = ft_count_word(s, c);
	strs = (char **)malloc((word + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	j = ft_split2(word, c, strs, (char *)s);
	if (j == -1)
		return (NULL);
	strs[j] = NULL;
	return (strs);
}
