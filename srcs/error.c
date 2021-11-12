/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:34:37 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/12 14:57:32 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *msg, int retur, int error)
{
	if (ft_strcmp(msg, "exit\n"))
		write(2, "MINISHELL : ", 12);
	write(2, msg, ft_strlen(msg));
	errno = error;
	return (retur);
}

char	**print_char_error(char *msg, int retur, int error, char *str)
{
	(void)retur;
	if (str)
		free (str);
	write(2, "MINISHELL : ", 12);
	write(2, msg, ft_strlen(msg));
	errno = error;
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
