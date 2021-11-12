/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:22:31 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/12 14:04:39 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_pipe(char *src, char *dest, int begin)
{
	int		i;
	int		j;
	char	c;

	c = src[begin];
	i = begin + 1;
	j = begin;
	dest[j] = '"';
	dest[++j] = c;
	dest[++j] = '"';
	while (src && dest && src[i])
	{
		dest[++j] = src[i];
		i++;
	}
	dest[++j] = '\0';
	return (dest);
}

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
	mini->old_ret = errno;
	if (mini->cmd)
		ft_cmd_clear(mini->cmd);
	if (mini->env)
		free_env(*mini->env);
	if (mini->envp && mini->f_envp)
		free_strs(mini->envp);
	if (mini->pid)
		free(mini->pid);
	exit (mini->old_ret);
}

int	child_pipe(t_cmd *cmd, int j, t_mini *mini)
{
	signal(SIGQUIT, sig_quit_daughter);
	if (cmd->next)
		if (dup2(mini->pipefd[j + 1], 1) < 0)
			return (-1);
	if (j != 0)
		if (dup2(mini->pipefd[j - 2], 0) < 0)
			return (-1);
	close_all_pipe(mini);
	return (0);
}

int	exe_pipe(t_mini *mini, t_cmd *cmd, int i)
{
	int		pid;
	int		j;
	int		last;
	char	*file;

	j = 2 * i;
	g_flag_fork = 1;
	file = redir_pipe(cmd->cmd, mini, &last);
	if (file == NULL && errno == -1)
		return (-1);
	pid = fork();
	if (pid != 0)
		mini->pid[i] = pid;
	if (pid == 0)
	{
		if (child_pipe(cmd, j, mini) == -1
			|| exe_redir_pipe(mini, file, last) == -1)
			return (-1);
		free_all(mini);
	}
	else if (pid == -1)
		return (print_error(strerror(errno), -1, errno));
	return (quit_red(mini, 0, file, 1));
}
