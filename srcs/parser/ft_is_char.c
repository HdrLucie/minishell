/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:56:11 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 16:03:58 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_spe_char(char c)
{
	if (c == '$' || c == '#')
		return (1);
	return (0);
}

int	is_redir(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c && c >= '\t' && c <= '\r')
		return (1);
	else if (c && c == ' ')
		return (1);
	return (0);
}

int	isnt_var(char *str, int *i)
{
	if ((ft_isdigit(str[*i]) || str[*i] == '?')
		&& str[*i - 1] && str[*i - 1] == '$')
	{
		*i = *i + 1;
		return (0);
	}
	else if (str[*i] == '_')
		return (1);
	if (ft_isalnum(str[*i]) == 0)
		return (0);
	return (1);
}
