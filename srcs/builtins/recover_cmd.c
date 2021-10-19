/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:58:20 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/19 15:39:30 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recover_cmd(t_mini	*mini)
{
	int	i = 0;
	if (mini->exe && mini->exe[0])
	{
		if (!ft_strcmp(mini->exe[0], "env"))
			print_env(*mini->env);
		else if (!ft_strcmp(mini->exe[0], "pwd"))
			print_pwd(*mini->env);
		else if (!ft_strncmp(mini->exe[0], "export", ft_strlen("export")))
			export_var(*mini->env, mini->exe);
		else if (!ft_strncmp(mini->exe[0], "unset", ft_strlen("unset")))
		{
			while (mini->exe[++i])
				unset_var(mini->env, mini->exe[i]);
		}
		else if (!ft_strcmp(mini->exe[0], "exit"))
			ft_exit(mini);
		else if (!ft_strncmp(mini->exe[0], "echo", ft_strlen("echo")))
			echo(mini->exe, *mini->env);
		else if (!ft_strncmp(mini->exe[0], "cd", ft_strlen("cd")))
			change_directory(*mini->env, mini->exe[1]);
		else
			return (2);
	}
	else
		return (2);
	return (1);
}
