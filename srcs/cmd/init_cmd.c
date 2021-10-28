/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 13:49:02 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char **cmd, t_mini *mini)
{
	int	pid;
	int	status;

	cmd[0] = parse_cmd(cmd[0], mini->envp);
	if (cmd[0] == NULL)
		return (print_error("PARSE PATH ERROR\n", -1));
	pid = fork();
	if (pid == -1)
		return (print_error("FORK ERROR\n", -1));
	if (pid == 0)
	{
		execve(cmd[0], cmd, mini->envp);
		perror("MINISHELL");
		exit(0);
	}
	waitpid(pid, &status, 0);
	mini->old_ret = status;
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
		tmp = mini->cmd;
		while (tmp)
		{
			if (tmp->pipe_in)
			{
				close(tmp->pipe_in[0]);
				close(tmp->pipe_in[1]);
				// free(tmp->pipe_in);
				tmp->pipe_in = NULL;
			}
			if (tmp->pipe_out)
			{
				close(tmp->pipe_out[0]);
				close(tmp->pipe_out[1]);
				// free(tmp->pipe_out);
				tmp->pipe_out = NULL;
			}
			tmp = tmp->next;
		}
		wait_child(mini->nb_pipe);
	}
	return (0);
}
