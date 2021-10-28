/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:21:45 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/28 14:30:27 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_str(char *str, char c, char a)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != c && str[i] != a)
			return (1);
		i++;
	}
	return (0);
}

int	echo(char **to_print)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	while (to_print[i])
	{
		if (is_in_str(to_print[i], '-', 'n') == 0)
		{
			new_line = 1;
			i++;
		}
		if (is_in_str(to_print[i], '-', 'n') == 1)
		{
			write(1, to_print[i], ft_strlen(to_print[i]));
			if (to_print[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (new_line == 0)
		write(1, "\n", 1);
	return (0);
}
