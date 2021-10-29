/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/29 13:55:22 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char **cmd, t_mini *mini)
{
	int	pid;
	int	status;

	cmd[0] = parse_cmd(cmd[0], mini->envp);
	if (cmd[0] == NULL)
		return (print_error("PARSE PATH ERROR\n", -1, errno));
	g_flag_fork = 1;
	pid = fork();
	if (pid == -1)
		return (print_error("FORK ERROR\n", -1, errno));
	if (pid == 0)
	{
		execve(cmd[0], cmd, mini->envp);
		print_error(strerror(errno), -1, errno);
		exit(127);
	}
	waitpid(pid, &status, 0);
	g_flag_fork = 0;
	if (WIFEXITED(status)) {
		mini->old_ret = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status)) {
		mini->old_ret = WTERMSIG(status);
	}
	return (0);
}

void	wait_child(int nb_pipe)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < nb_pipe + 1)
	{
		wait(&status);
		i++;
	}
	g_flag_fork = 0;
}

int	ft_execute_cmd(t_mini *mini)
{
	t_cmd	*tmp;

	tmp = mini->cmd;
	if (mini->nb_pipe == 0)
	{
		if (tmp->cmd && redir(tmp->cmd, mini) == -1)
			return (-1);
	}
	else
	{
		while (tmp)
		{
			if (tmp->cmd && exe_pipe(mini, tmp) == -1)
				return (-1);
			tmp = tmp->next;
		}
		close_all_pipe(mini->cmd);
		wait_child(mini->nb_pipe);
	}
	return (0);
}
