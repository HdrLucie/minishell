/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:53:09 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/08 13:37:25 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_car_spe(char *str, int i)
{
	while (str && str[i] && !(is_space(str[i]) || str[i] == '|'
			|| (str[i + 1] == '|' && str[i] != '"')
			|| is_redir(str[i]) || is_spe_char(str[i])))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = find_token(str, i, str[i]);
			if (str[i] && str[i + 1] && str[i + 1] == '|')
				break ;
		}
		else
			i++;
		if (i == -1)
			return (-1);
	}
	if (str && str[i] && str[i] != ' ' && (str[i] == '|'
			|| str[i + 1] == '|'))
		i++;
	return (i);
}

int	check_quote(char *str, int i)
{
	if (str[i] == '#')
		return (find_token(str, i, '\n'));
	else if (ft_isdigit(str[i]))
	{
		if (str[i + 1] && is_redir(str[i + 1]))
		{
			if (str[i + 2] && is_redir(str[i + 2]))
				return (i + 3);
			return (i + 2);
		}
	}
	else if (is_redir(str[i]))
	{
		if (str[i + 1] && is_redir(str[i + 1]))
			return (i + 2);
		return (i + 1);
	}
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
