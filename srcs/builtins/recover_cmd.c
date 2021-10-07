/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:58:20 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/07 14:56:31 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recover_cmd(char **cmd, t_env **env, t_cmd *lst)
{
	if (!ft_strcmp(cmd[0], "env"))
		ft_print_env(*env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		print_pwd(*env);
	else if (!ft_strncmp(cmd[0], "export", ft_strlen("export")))
		ft_export_var(*env, cmd[1]);
	else if (!ft_strncmp(cmd[0], "unset", ft_strlen("unset")))
		ft_unset_var(env, cmd[1]);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(*env, lst);
	else
		return (2);
	return (1);
}
