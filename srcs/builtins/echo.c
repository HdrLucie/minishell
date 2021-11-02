/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:21:45 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/02 12:22:32 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_char(char *str, char c)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	is_in_str_echo(char **str)
{
	int	i;
	int	j;
	int	ret;

	i = 1;
	j = 0;
	ret = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] != '-' && only_char(str[i], 'n') == 0)
				return (ret);
			else
				j++;
		}
		j = 0;
		ret += 1;
		i++;
	}
	return (ret);
}

int	echo(char **to_print)
{
	int	i;
	int	new_line;
	int	ret;

	i = 1;
	new_line = 0;
	ret = 0;
	ret = is_in_str_echo(to_print);
	if (ret > 0)
	{
		new_line = 1;
		i += ret;
	}
	while (to_print[i])
	{
		write(1, to_print[i], ft_strlen(to_print[i]));
		if (to_print[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == 0)
		write(1, "\n", 1);
	return (0);
}
