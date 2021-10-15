/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:56:11 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/14 11:42:04 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_spe_char(char *str, int i)
{
	if (i == 0 || str[i - 1] != '\\')
	{
		if (str[i] == '\"' || str[i] == '\''
			|| str[i] == '$' || str[i] == '#' || str[i] == '=')
			return (1);
	}
	return (0);
}

int	is_redir(char *str, int i)
{
	if (i == 0 || str[i - 1] != '\\')
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == ';')
			return (1);
	}
	return (0);
}

int	is_space(char *str, int i)
{
	if (i == 0 || str[i - 1] != '\\')
	{
		if (str[i] && str[i] >= '\t' && str[i] <= '\r')
			return (1);
		else if (str[i] && str[i] == ' ')
			return (1);
	}
	return (0);
}
