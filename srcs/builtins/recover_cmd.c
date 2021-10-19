/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:58:20 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/19 14:50:07 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recover_cmd(char **cmd, t_env **env, t_cmd *lst)
{
	int	i = 0;
	if (cmd && cmd[0])
	{
		if (!ft_strcmp(cmd[0], "env"))
			print_env(*env);
		else if (!ft_strcmp(cmd[0], "pwd"))
			print_pwd(*env);
		else if (!ft_strncmp(cmd[0], "export", ft_strlen("export")))
			export_var(*env, cmd);
		else if (!ft_strncmp(cmd[0], "unset", ft_strlen("unset")))
		{
			while (cmd[++i])
				unset_var(env, cmd[i]);
		}
		else if (!ft_strcmp(cmd[0], "exit"))
			ft_exit(*env, lst, cmd);
		else if (!ft_strncmp(cmd[0], "echo", ft_strlen("echo")))
			echo(cmd, *env);
		else if (!ft_strncmp(cmd[0], "cd", ft_strlen("cd")))
			change_directory(*env, cmd[1]);
		else
			return (2);
	}
	else
		return (2);
	return (1);
}
