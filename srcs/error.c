/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:34:37 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 09:37:40 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *msg, int retur)
{
	write(2, "MINISHELL : ", 12);
	write(2, msg, ft_strlen(msg));
	return (retur);
}

char	**print_char_error(char *msg, int retur)
{
	write(2, "MINISHELL : ", 12);
	write(2, msg, ft_strlen(msg));
	if (retur == -1)
		errno = -1;
	return (NULL);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
}
