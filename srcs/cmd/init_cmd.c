/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/12 11:00:52 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_execution(char **cmd, t_mini *mini)
{
	signal(SIGQUIT, sig_quit_daughter);
	errno = 0;
	execve(cmd[0], cmd, mini->envp);
	perror("EXECVE");
	ft_exit(mini, 0);
	exit(127);
}

int	execute(char **cmd, t_mini *mini)
{
	int	pid;
	int	status;

	cmd[0] = parse_cmd(cmd[0], mini->envp);
	if (cmd[0] == NULL)
		return (-1);
	if (g_flag_fork != 3)
		g_flag_fork = 1;
	pid = fork();
	if (pid == -1)
		return (print_error("FORK ERROR\n", -1, errno));
	if (pid == 0)
		child_execution(cmd, mini);
	waitpid(pid, &status, 0);
	signal_ret(status, mini);
	if (g_flag_fork != 3)
		g_flag_fork = 0;
	errno = mini->old_ret;
	return (0);
}

void	wait_child(t_mini *mini)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	close_all_pipe(mini);
	while (i < mini->nb_pipe + 1)
	{
		waitpid(mini->pid[i], &status, 0);
		i++;
	}
	free(mini->pid);
	if (g_flag_fork != 3)
		g_flag_fork = 0;
	signal_ret(status, mini);
}

int	init_pipe(t_mini *mini)
{
	int	i;

	mini->pipefd = malloc(sizeof(int) * 2 * mini->nb_pipe);
	if (mini->pipefd == NULL)
		return (print_error("ALLOCATION PIPE FAILED\n", -1, -1));
	i = -1;
	while (++i < mini->nb_pipe)
		if (pipe(mini->pipefd + i * 2) == -1)
			return (print_error("PIPE FAILED\n", -1, -1));
	mini->pid = malloc(sizeof(int) * (mini->nb_pipe + 1));
	if (mini->pid == NULL)
		return (print_error(strerror(errno), -1, -1));
	return (0);
}

int	ft_execute_cmd(t_mini *mini)
{
	int		ret;

	if (mini->nb_pipe == 0 && mini->cmd->cmd)
	{
		ret = redir(mini->cmd->cmd, mini);
		if (errno == -3)
			errno = 0;
		if (mini->old_ret == 0)
			mini->old_ret = errno;
		if (ret < 0)
			return (ret);
	}
	else
	{
		if (run_every_pipe(mini) == -1)
			return (-1);
		wait_child(mini);
	}
	return (0);
}
