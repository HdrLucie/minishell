/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:21:45 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/22 14:49:43 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **to_print)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	if (!to_print[1])
		return (-2);
	while (to_print[i])
	{
		if (to_print[i][0] == '-' && to_print[i][1] == 'n')
			new_line = 1;
		else
		{
			write(1, to_print[i], ft_strlen(to_print[i]));
			if (to_print[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	if (new_line == 0)
		write(1, "\n", 1);
	return (0);
}
