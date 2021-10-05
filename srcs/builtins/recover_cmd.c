/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:58:20 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/05 16:49:42 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recover_cmd(char **cmd, t_env *env)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "env"))
			ft_print_env(env);
		else if (!ft_strcmp(cmd[i], "pwd"))
			print_pwd(env);
		else if (!ft_strncmp(cmd[i], "export", ft_strlen("export")))
			ft_export_var(env, cmd[1]);
		else if (!ft_strncmp(cmd[i], "unset", ft_strlen("unset")))
			ft_unset_var(&env, cmd[1]);
		else if (!ft_strcmp(cmd[i], "exit"))
			ft_exit(env);
		else
			return (2);
		i++;
	}
	return (1);
}
