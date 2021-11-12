/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:44:41 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/12 12:04:06 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*erase_copy(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src && dest && src[i] && dest[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**remove_quote(char **token)
{
	int		i;
	int		j;
	char	c;

	j = 0;
	while (token[j])
	{
		i = 0;
		while (token[j][i])
		{
			if (token[j][i] == '\"' || token[j][i] == '\'')
			{
				c = token[j][i];
				erase_copy(&token[j][i + 1], &token[j][i]);
				while (token[j][i] && token[j][i] != c)
					i++;
			}
			else
				i++;
		}
		j++;
	}
	return (token);
}
