/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:53:09 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/04 11:38:04 by ehautefa         ###   ########.fr       */
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
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '('
			&& find_token(str, &i, ')') == -1)
			return (-1);
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '{'
			&& find_token(str, &i, '}') == -1)
			return (-1);
	}
	while (str[i] && !(is_space(str[i], str[i - 1])
			|| str[i] == '\"' || str[i] == '\''
			|| str[i] == '$' || str[i] == '#' || str[i] == '|'
			|| str[i] == '>' || str[i] == '<'))
		i++;
	if (str[i] == '=')
		i++;
	return (i);
}

int	is_space(char c, char prev)
{
	if (prev && (prev == '\\' || prev == '='))
		return (0);
	else if (c >= '\t' && c <= '\r')
		return (1);
	else if (c == ' ')
		return (1);
	else
		return (0);
}