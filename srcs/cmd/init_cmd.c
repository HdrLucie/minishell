/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/06 14:12:44 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char **cmd, char **envp)
{
	int	pid;

	cmd[0] = parse_cmd(cmd[0]);
	if (cmd[0] == NULL)
		return (print_error("PARSE PATH ERROR\n", -1));
	pid = fork();
	if (pid == -1)
		return (print_error("FORK ERROR\n", -1));
	if (pid == 0)
	{
		execve(cmd[0], cmd, envp);
		perror("MINISHELL");
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	ft_execute_cmd(t_cmd *cmd, char **envp, t_env *env_lst)
{
	while (cmd)
	{
		if (cmd->cmd && ft_recover_cmd(cmd->cmd, env_lst) == 2)
		{
			if (cmd->cmd && execute(cmd->cmd, envp))
				return (-1);
		}
		cmd = cmd->next;
	}
	return (0);
}
