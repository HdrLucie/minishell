/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:00:10 by ehautefa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/04 09:37:59 by ehautefa         ###   ########.fr       */
=======
/*   Updated: 2021/10/04 14:53:21 by ehautefa         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char **cmd, char **envp)
{
	int	pid;

	cmd[0] = parse_cmd(cmd[0]);
	if (cmd[0] == NULL)
<<<<<<< HEAD
		return (print_error("PARSE PATH ERROR", -1));
	pid = fork();
	if (pid == -1)
		return (print_error("FORK ERROR", -1));
=======
		return (print_error("PARSE PATH ERROR\n", -1));
	pid = fork();
	if (pid == -1)
		return (print_error("FORK ERROR\n", -1));
>>>>>>> main
	if (pid == 0)
	{
		execve(cmd[0], cmd, envp);
		perror("MINISHELL");
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	ft_execute_cmd(t_cmd *cmd, char **envp)
{
	while (cmd)
	{
<<<<<<< HEAD
		if (cmd->cmd != NULL && execute(cmd->cmd, envp))
=======
		if (cmd->cmd && execute(cmd->cmd, envp))
>>>>>>> main
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
