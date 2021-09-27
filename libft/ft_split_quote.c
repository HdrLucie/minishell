/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:16:19 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/27 12:19:00 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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
		if (str[i] == '\"')
		{
			printf("%s\n", &str[i]);
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] != '\"')
				return (-1);
			i++;
			printf("%s\n\n", &str[i]);
		}
		else
			while (str[i] && !((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ' || str[i] == '\"'))
				i++;
	}
	return (word);
}

int	size_word(char *str, int *k)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
		i++;
	*k = i;
	if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
	}
	else
		while (str[i] && !((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
			i++;
	return (i - *k);
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
		printf("size : %d : %s : %d\n", size, &str[k], k);
		size = size_word(&str[k], &k);
		printf("size : %d : %s : %d\n", size, &str[k], k);
		split[j] = malloc((size + 1) * sizeof(**split));
		if (split[j] == NULL)
			return (NULL);
		while (++i < size + 1)
			split[j][i] = str[k++];
		printf("k : %d\n", k);
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
	printf("%d\n", word);
	if (word == -1)
		return (NULL);
	split = malloc((word + 1) * sizeof(*split));
	if (split == NULL)
		return (NULL);
	split = fill_split(str, split, word);
	return (split);
}

int	main ()
{
	char **split = NULL;
	int	i;
	char str[50]= "Comment \"vas\"-tu pipoupa\"hhhh\" ";
	(void)str;
	split = ft_split_quote(str);
	i = 0;
	while (split && split[i])
	{
		printf("%s\n", split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	printf("\n");
	
}