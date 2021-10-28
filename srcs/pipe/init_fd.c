/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 09:09:42 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 11:34:12 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe(t_mini *mini)
{
	t_cmd	*tmp;
	int		f_begin;
	int		*fd;
	
	f_begin = 1;
	tmp = mini->cmd;
	tmp->pipe_in = NULL;
	tmp->pipe_out = NULL;
	mini->nb_pipe = 0;
	while (tmp)
	{
		if (f_begin)
			f_begin = 0;
		if (tmp->next)
		{
			fd = malloc(2 * sizeof(int));
			if (fd == NULL)
				return (-1);
			if (pipe(fd) == -1)
			{
				perror("SHELLA ");
				return (-1);
			}
			tmp->pipe_out = fd;
			tmp->next->pipe_in = fd;
		}
		mini->nb_pipe++;
		tmp = tmp->next;
	}
	return (0);
}