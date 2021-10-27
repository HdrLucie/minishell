/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/27 12:51:07 by ehautefa         ###   ########.fr       */
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
void	ft_print_list(t_cmd *tmp2);
int	ft_execute_cmd(t_mini *mini)
{
	t_cmd	*tmp;

	tmp = mini->cmd;
	ft_print_list(tmp);
	while (tmp)
	{
		// if (tmp->pipe_out)
		// 	printf("INIT : 0 : %d 1: %d\n", tmp->pipe_out[0], tmp->pipe_out[1]);
		if (tmp->cmd && exe_pipe(mini, tmp) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
