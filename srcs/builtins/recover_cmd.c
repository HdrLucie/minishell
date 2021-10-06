/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:58:20 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/06 18:57:19 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recover_cmd(char **cmd, t_env *env)
{
	if (!ft_strcmp(cmd[0], "env"))
		ft_print_env(env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		print_pwd(env);
	else if (!ft_strncmp(cmd[0], "export", ft_strlen("export")))
		ft_export_var(env, cmd[1]);
	else if (!ft_strncmp(cmd[0], "unset", ft_strlen("unset")))
	{
		printf("\nBEFORE UNSET\n\n");
		ft_print_env(env);
		ft_unset_var(&env, cmd[1]);
		printf("\nAFTER UNSET\n\n");
		ft_print_env(env);
	}
	else if (!ft_strcmp(cmd[0], "exit"))
	{
		printf("EXIT : %s\n", (env)->name);
		ft_exit(env);
	}
	else
		return (2);
	return (1);
}
