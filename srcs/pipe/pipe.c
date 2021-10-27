/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:22:31 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/27 12:50:35 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipe(int *fd, int fd_std, int pid)
{
	printf("PID : %d, fd[fd_std] : %d %d\n",pid, fd[fd_std], fd[!fd_std]);
	close(fd[fd_std]);
	if (dup2(fd[!fd_std], fd_std) == -1)
		return (print_error(strerror(errno), -1));
	close(fd[!fd_std]);
	printf("PID : %d, fd[fd_std] : %d %d\n", pid, fd[fd_std], fd[!fd_std]);
	return (0);
}

int	exe_pipe(t_mini *mini, t_cmd *cmd)
{
	int pid;
	int	ret;

	ret = 0;
	(void)mini;
	if (cmd->pipe_in)
		printf("IN : 0 : %d 1: %d\n", cmd->pipe_in[0], cmd->pipe_in[1]);
	if (cmd->pipe_out)
		printf("OUT : 0 : %d 1: %d\n", cmd->pipe_out[0], cmd->pipe_out[1]);
	if (cmd->pipe_out)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("SAlut c'est moi Lucette \n\n");
			printf("FCNTL of %d : %d\n", cmd->pipe_out[0], fcntl(cmd->pipe_out[0], 0, F_GETFL));
			exe_pipe(mini, cmd->next);
			exit(0);
		}
	}
	if (cmd->pipe_in)
		if (execute_pipe(cmd->pipe_in, 1, pid) == -1)
			return (-1);
	if (cmd->pipe_out)
		if (execute_pipe(cmd->pipe_out, 0, pid))
			return (-1);
	ret = redir(cmd->cmd, mini);
	if (ret == -1)
		return (-1);
			printf(" PID : %d SAlut c'est moi Ginette \n\n", pid);

	waitpid(pid, NULL, 0);
	return (ret);
}