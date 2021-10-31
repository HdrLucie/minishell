/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:22:31 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/31 13:38:06 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipe(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < 2 * mini->nb_pipe)
	{
		close(mini->pipefd[i]);
		i++;
	}
	free(mini->pipefd);
}

void	free_all(t_mini *mini)
{
	if (mini->cmd)
		ft_cmd_clear(mini->cmd);
	if (mini->env)
		free_env(*mini->env);
	if (mini->envp && mini->f_envp)
		free_strs(mini->envp);
	if (mini->pid)
		free(mini->pid);
	exit (0);
}

int	exe_pipe(t_mini *mini, t_cmd *cmd, int i)
{
	int	pid;
	int	j;

	j = 2 * i;
	g_flag_fork = 1;
	pid = fork();
	if (pid != 0)
		mini->pid[i] = pid;
	if (pid == 0)
	{
		if (cmd->next)
			if (dup2(mini->pipefd[j + 1], 1) < 0)
				return (-1);
		if (j != 0)
			if (dup2(mini->pipefd[j - 2], 0) < 0)
				return (-1);
		close_all_pipe(mini);
		if (redir(cmd->cmd, mini) == -1)
			exit (-1);
		free_all(mini);
	}
	else if (pid == -1)
		return (print_error(strerror(errno), -1, errno));
	return (0);
}
