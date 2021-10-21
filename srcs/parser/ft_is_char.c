/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:56:11 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/21 12:38:46 by elise            ###   ########.fr       */
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
	if (c == '>' || c == '<' || c == ';')
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
