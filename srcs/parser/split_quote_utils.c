/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:53:09 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/20 16:23:57 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_export(char *str, int i)
{
	if (str[i] != '=')
		return (print_error("UNCLOSED QUOTTE\n", -1));
	i++;
	if (str[i++] == '\"')
	{
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i] != '\"')
			return (print_error("UNCLOSED QUOTE\n", -1));
		i++;
	}
	else
		while (str[i] && !is_space(str[i]))
			i++;
	return (i);
}

int	check_car_spe(char *str, int i)
{
	while (str && str[i] && !(is_space(str[i]) || is_redir(str[i])
			|| is_redir(str[i + 1]) || is_spe_char(str[i])))
		i++;
	if (str && str[i] && str[i] == '=')
	{
		i = parse_export(str, i);
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
	if (str[i] == '\"')
		return (find_token(str, i, '\"'));
	if (str[i] == '\'')
		return (find_token(str, i, '\''));
	else if (str[i] == '#')
		return (find_token(str, i, '\n'));
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == '(')
		return (find_token(str, i, ')'));
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == '{')
		return (find_token(str, i, '}'));
	else if (str[i] == '$')
		return (find_token(str, i, ' '));
	return (check_car_spe(str, i));
}
