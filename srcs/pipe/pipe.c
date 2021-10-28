/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:22:31 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 18:54:31 by hlucie           ###   ########.fr       */
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

void	free_all(t_mini *mini)
{
	if (mini->cmd)
		ft_cmd_clear(mini->cmd);
	if (mini->env)
		free_env(*mini->env);
	if (mini->envp && mini->f_envp)
		free_strs(mini->envp);
	exit (0);
}

int	exe_pipe(t_mini *mini, t_cmd *cmd)
{
	int	pid;
	int	ret;

	ret = 0;
	g_flag_fork = 1;
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
		free_all(mini);
	}
	else if (pid == -1)
		return (print_error("FORK FUCKING FAILED !!!", -1));
	return (0);
}
