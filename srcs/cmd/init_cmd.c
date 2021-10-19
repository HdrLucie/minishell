/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/19 12:51:36 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char **cmd, char **envp)
{
	int	pid;
	int	ret;

	ret = 0;
	cmd[0] = parse_cmd(cmd[0], envp);
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

int	ft_execute_cmd(t_mini *mini)
{
	t_cmd	*tmp;

	tmp = mini->cmd;
	while (tmp)
	{
		if (tmp->cmd && redir(tmp->cmd, mini) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
