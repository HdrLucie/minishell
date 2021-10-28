/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:22:31 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 15:51:05 by hlucie           ###   ########.fr       */
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

int	exe_pipe(t_mini *mini, t_cmd *cmd)
{
	int pid;
	int	ret;

	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		if (cmd->pipe_out)
		{
			close(cmd->pipe_out[0]);
			if (dup2(cmd->pipe_out[1], 1) == -1)
			{
				print_error("FUCK OF THIS FUCKING SHIT !!!", -1);
				exit (-1);
			}
			close(cmd->pipe_out[1]);
		}
		if (cmd->pipe_in)
		{
			close(cmd->pipe_in[1]);
			if (dup2(cmd->pipe_in[0], 0) == -1)
			{
				print_error("FUCK OF THIS FUCKING SHIT !!!", -1);
				exit (-1);
			}
			close(cmd->pipe_in[0]);
		}
		ret = redir(cmd->cmd, mini);
		if (ret == -1)
			exit (-1);
		ft_exit(mini);
	}
	else if (pid == -1)
	{
		print_error("FORK FUCKING FAILED !!!", -1);
		exit (-1);
	}
	return (0);
}
