/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:58:20 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/18 10:55:53 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recover_cmd(char **cmd, t_env **env, t_cmd *lst)
{
	if (cmd && cmd[0])
	{
		if (!ft_strcmp(cmd[0], "env"))
			print_env(*env);
		else if (!ft_strcmp(cmd[0], "pwd"))
			print_pwd(*env);
		else if (!ft_strncmp(cmd[0], "export", ft_strlen("export")))
			export_var(*env, cmd);
		else if (!ft_strncmp(cmd[0], "unset", ft_strlen("unset")))
			unset_var(env, cmd[1]);
		else if (!ft_strcmp(cmd[0], "exit"))
			ft_exit(*env, lst, cmd);
		else if (!ft_strncmp(cmd[0], "echo", ft_strlen("echo")))
			echo(cmd, *env);
		else if (!ft_strncmp(cmd[0], "cd", ft_strlen("cd")))
			change_directory(*env, cmd);
		else
			return (2);
	}
	else
		return (2);
	return (1);
}
