/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/30 09:14:05 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	parse_redire(char **split, t_cmd cmd)
// {
// 	int	fd;

// 	fd = 1;
// 	if (split[0][0] >= '0' && split[0][0] <= '9')
// 		fd = split[0][0];
// 	else if (split[0][0] == '>' || split[0][0] == '<')
// 	else

// }

// int	parser(char **split, char **envp)
// {
// 	t_cmd	**cmd;
// 	int		j;

// 	(void)envp;
// 	j = -1;
// 	while (split[j])
// 	{
// 		if (split[j][0] == '>' || split[j][0] == '<'
// 			|| ((split[j][1] == '>'|| split[j][1] == '<')
// 			&& split[j][0] != '\\'))
// 			parse_redir(&split[j], cmd);
// 	}
	
// }



// int	exec(t_cmd **cmd)
// {
// 	if (cmd->built_in == 0)
// 		if (parse_cmd(split[0]) == -1)
	// 	return (print_error("ALLOCATION FAILED\n", -1));
	// int i	= -1;
	// while (split[++i])
	// 	printf("%s\n", split[i]);
 	// execve(split[0], split, envp);
	// perror("MINISHELL");
	// return (0);
// 	else
// 		dispatch(&cmd);

// }

// int dispatch()
// if (ft_strcmp(cmd->cmd[0], "cd"))
