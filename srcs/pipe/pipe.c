/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:22:31 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 13:51:03 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipe(int *fd, int fd_std)
{
	close(fd[!fd_std]);
	if (dup2(fd[fd_std], fd_std) == -1)
		return (print_error("FUCK OF THIS FUCKING SHIT !!!", -1));
	close(fd[fd_std]);
	return (0);
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	fd = NULL;
}

void	close_all_pipe(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe_in)
			close_pipe(cmd->pipe_in);
		if (cmd->pipe_out)
			close_pipe(cmd->pipe_out);
		cmd = cmd->next;
	}
}

int	exe_pipe(t_mini *mini, t_cmd *cmd)
{
	int	pid;
	int	ret;

	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		if (cmd->pipe_out)
			if (execute_pipe(cmd->pipe_out, 1) == -1)
				return (-1);
		if (cmd->pipe_in)
			if (execute_pipe(cmd->pipe_in, 0) == -1)
				return (-1);
		ret = redir(cmd->cmd, mini);
		if (ret == -1)
			exit (-1);
		exit(0);
	}
	else if (pid == -1)
		return (print_error("FORK FUCKING FAILED !!!", -1));
	return (0);
}
