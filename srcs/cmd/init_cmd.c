/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/04 08:38:12 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char **cmd, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	(void)cmd;
	return (0);
}

int	ft_execute_cmd(t_cmd *cmd, char **envp)
{
	while (cmd)
	{
		if (execute(cmd->cmd, envp))
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}

int	fill_cmd(char **token, char **envp)
{
	t_cmd	*cmd;

	(void)envp;
	cmd = ft_cmd_new(token, 1, (t_redir *)0, (t_redir *)0);
	if (cmd == NULL)
		return (-1);
	ft_execute_cmd(cmd, envp);
	return (0);
}
