/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 09:09:42 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 18:55:02 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_fd(t_cmd *tmp, int f_begin)
{
	int		*fd;

	if (f_begin)
		f_begin = 0;
	if (tmp->next)
	{
		fd = malloc(2 * sizeof(int));
		if (fd == NULL)
			return (print_error(strerror(errno), -1));
		if (pipe(fd) == -1)
			return (print_error(strerror(errno), -1));
		tmp->pipe_out = fd;
		tmp->next->pipe_in = fd;
	}
	return (0);
}

int	init_pipe(t_mini *mini)
{
	t_cmd	*tmp;
	int		f_begin;

	f_begin = 1;
	tmp = mini->cmd;
	mini->nb_pipe = 0;
	tmp->pipe_in = NULL;
	while (tmp)
	{
		tmp->pipe_out = NULL;
		if (create_fd(tmp, f_begin) == -1)
			return (-1);
		mini->nb_pipe++;
		tmp = tmp->next;
	}
	mini->nb_pipe--;
	return (0);
}
