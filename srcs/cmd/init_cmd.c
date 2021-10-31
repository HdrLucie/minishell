/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/31 13:26:48 by elisehautef      ###   ########.fr       */
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
		perror("EXECVE");
		ft_exit(mini, 0);
		exit(127);
	}
	waitpid(pid, &status, 0);
	g_flag_fork = 0;
	if (WIFEXITED(status)) {
		mini->old_ret = WEXITSTATUS(status);
	}
	return (0);
}

void	wait_child(t_mini *mini)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	
	while (i < mini->nb_pipe + 1)
	{
		waitpid(mini->pid[i], &status, 0);
		i++;
	}
	free(mini->pid);
	g_flag_fork = 0;
}

int	init_pipe(t_mini *mini)
{
	int	i;

	mini->pipefd = malloc(sizeof(int) * 2 * mini->nb_pipe);
	if (mini->pipefd == NULL)
		return (print_error("ALLOCATION PIPE FAILED\n", -1, -1));
	i = 0;
	while (i < mini->nb_pipe)
	{
    	if (pipe(mini->pipefd + i * 2) == -1) 
			return (print_error("PIPE FAILED\n", -1, -1));
		i++;
    }
	return (0);
}


int	ft_execute_cmd(t_mini *mini)
{
	t_cmd	*tmp;
	int		i;
	
	tmp = mini->cmd;
	if (mini->nb_pipe == 0)
	{
		if (tmp->cmd && redir(tmp->cmd, mini) == -1)
			return (-1);
	}
	else
	{
		if (init_pipe(mini) == -1)
			return (-1);
		mini->pid = malloc(sizeof(int) * (mini->nb_pipe + 1));
		if (mini->pid == NULL)
			return (print_error(strerror(errno), -1, -1));
		i = 0;
		while (tmp)
		{
			if (tmp->cmd && exe_pipe(mini, tmp, i) == -1)
				return (-1);
			i++;
			tmp = tmp->next;
		}
		close_all_pipe(mini);
		wait_child(mini);
	}
	return (0);
}
