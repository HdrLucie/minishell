/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/07 17:22:58 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char **cmd, char **envp)
{
	int	pid;
	int	ret;

	ret = 0;
	cmd[0] = parse_cmd(cmd[0]);
	if (cmd[0] == NULL)
		return (print_error("PARSE PATH ERROR\n", -1));
	pid = fork();
	if (pid == -1)
		return (print_error("FORK ERROR\n", -1));
	if (pid == 0)
	{
		ret = execve(cmd[0], cmd, envp);
		perror("MINISHELL");
		exit(ret);
	}
	waitpid(pid, NULL, 0);
	return (ret);
}

int	ft_execute_cmd(t_cmd *cmd, char **envp, t_env **env_lst)
{
	int		ret;
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		// redir(cmd);
		if (cmd->cmd)
		{
			ret = recover_cmd(cmd->cmd, env_lst, tmp);
			if (cmd->cmd && ret == 2)
			{
				ret = execute(cmd->cmd, envp);
				if (ret == -1)
					return (ret);
			}
		}
		cmd = cmd->next;
	}
	// ft_print_list(cmd);
	return (ret);
}
