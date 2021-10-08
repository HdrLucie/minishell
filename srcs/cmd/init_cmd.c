/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/08 17:43:14 by elisehautef      ###   ########.fr       */
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
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		if (cmd->cmd && redir(cmd->cmd, tmp, envp, env_lst) == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}
