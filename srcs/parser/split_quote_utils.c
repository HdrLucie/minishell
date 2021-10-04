/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:53:09 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/04 09:54:32 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (str[i] && !((str[i] >= '\t' && str[i] <= '\r')
			|| str[i] == ' ' || str[i] == '\"' || str[i] == '\''
			|| str[i] == '$' || str[i] == '#' || str[i] == '|'
			|| str[i] == '>' || str[i] == '<'))
		i++;
	return (++i);
}