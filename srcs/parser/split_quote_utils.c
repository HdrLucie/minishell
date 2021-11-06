/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:53:09 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/06 16:52:43 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_car_spe(char *str, int i)
{
	while (str && str[i] && !(is_space(str[i]) || is_redir(str[i])
			|| is_redir(str[i + 1]) || is_spe_char(str[i])))
	{
		if (str[i] == '\"')
			i = find_token(str, i, '\"');
		else if (str[i] == '\'')
			i = find_token(str, i, '\'');
		else
			i++;
		if (i == -1)
			return (-1);
	}
	if (str && str[i] && str[i] != ' ' && (is_redir(str[i])
			|| is_redir(str[i + 1])))
		i++;
	return (i);
}

int	check_quote(char *str, int i)
{
	if (str[i] == '#')
		return (find_token(str, i, '\n'));
	return (check_car_spe(str, i));
}

char	**remove_comments(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (split[i][0] == '#')
		{
			while (split[i])
			{
				free(split[i]);
				split[i] = NULL;
				i++;
			}
		}
		i++;
	}
	return (split);
}
