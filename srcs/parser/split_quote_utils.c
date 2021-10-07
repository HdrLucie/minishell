/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:53:09 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/07 10:02:35 by ehautefa         ###   ########.fr       */
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
		while (str[i] && !is_space(str, i))
			i++;
	return (i);
}

int	check_car_spe(char *str, int i)
{
	while (str[i] && !(is_space(str, i) || is_redir(str, i)
			|| is_redir(str, i + 1) || is_spe_char(str, i)))
		i++;
	if (str[i] == '=')
	{
		i = parse_export(str, i);
		if (i == -1)
			return (-1);
	}
	if (str[i] != ' ' && (is_redir(str, i) || is_redir(str, i + 1)))
		i++;
	return (i);
}

int	check_quote(char *str, int i)
{
	if (!(str[i - 1] && str[i - 1] == '\\'))
	{
		if (str[i] == '\"' && find_token(str, &i, '\"') == -1)
			return (print_error("UNCLOSED QUOTE\n", -1));
		else if (str[i] == '\'' && find_token(str, &i, '\'') == -1)
			return (print_error("UNCLOSED QUOTE\n", -1));
		else if (str[i] == '#' && find_token(str, &i, '\n') == -1)
			return (i);
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '('
			&& find_token(str, &i, ')') == -1)
			return (print_error("UNCLOSED BRACKET\n", -1));
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '{'
			&& find_token(str, &i, '}') == -1)
			return (print_error("UNCLOSED BRACKET\n", -1));
		else if (str[i] == '$' && find_token(str, &i, ' ') == -1)
			return (i);
	}
	return (check_car_spe(str, i));
}

int	is_spe_char(char *str, int i)
{
	if ((str[i - 1] && str[i - 1] == '\\') || !str[i])
		return (0);
	else if (str[i] == '\"' || str[i] == '\''
			|| str[i] == '$' || str[i] == '#' || str[i] == '=')
		return (1);
	else
		return (0);
}

int	is_redir(char *str, int i)
{
	if ((str[i - 1] && str[i - 1] == '\\') || !str[i])
		return (0);
	else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (1);
	else
		return (0);
}

int	is_space(char *str, int i)
{
	if (str[i - 1] && (str[i - 1] == '\\' || str[i - 1] == '='))
		return (0);
	else if (str[i] && str[i] >= '\t' && str[i] <= '\r')
		return (1);
	else if (str[i] && str[i] == ' ')
		return (1);
	else
		return (0);
}
