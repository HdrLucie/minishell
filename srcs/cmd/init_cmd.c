/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/29 19:54:00 by ehautefa         ###   ########.fr       */
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
	write(9, cmd[0], ft_strlen(cmd[0]));
	write(9, "\n", 1);
	ft_putnbr_fd(pid, 9);
	write(9, "\n", 1);
	waitpid(pid, &status, WNOHANG);
	g_flag_fork = 0;
	if (WIFEXITED(status)) {
		mini->old_ret = WEXITSTATUS(status);
		write(9, "SALUTT\n", 7);

	}
	if (WIFSIGNALED(status)) {
		mini->old_ret = WTERMSIG(status);
		write(9, "COUCOU\n", 7);
	}
	return (0);
}

void	wait_child(t_mini *mini)
{
	int	i;
	int	status;

	i = mini->nb_pipe + 1;
	status = 0;
	while (!mini->pid[i])
		;
	while (i > 0)
	{
		waitpid(mini->pid[i], &status, WUNTRACED);
		i--;
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
		mini->pid = malloc(sizeof(int) * (mini->nb_pipe + 1));
		if (mini->pid == NULL)
			return (print_error(strerror(errno), -1, -1));
		while (tmp)
		{
			if (tmp->cmd && exe_pipe(mini, tmp) == -1)
				return (-1);
			tmp = tmp->next;
		}
		wait_child(mini);
		close_all_pipe(mini->cmd);

	}
	return (0);
}
