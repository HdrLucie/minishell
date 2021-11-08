/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:58:20 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/03 14:39:54 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recover_cmd_part_2(t_mini *mini)
{
	if (!ft_strcmp(mini->exe[0], "exit"))
		ft_exit(mini, 1);
	else if (!ft_strcmp(mini->exe[0], "echo"))
		mini->old_ret = echo(mini->exe);
	else if (!ft_strcmp(mini->exe[0], "pwd"))
		mini->old_ret = print_pwd();
	else if (!ft_strncmp(mini->exe[0], "export", ft_strlen("export")))
		mini->old_ret = export_var(*mini->env, mini->exe);
	else if (!ft_strncmp(mini->exe[0], "cd", ft_strlen("cd")))
		mini->old_ret = change_directory(*mini->env, mini->exe[0],
				mini->exe[1]);
	else
		return (2);
	return (1);
}

int	recover_cmd(t_mini	*mini)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (mini->exe && mini->exe[0])
	{
		if (!ft_strcmp(mini->exe[0], "env"))
			print_env(*mini->env);
		else if (!ft_strncmp(mini->exe[0], "unset", ft_strlen("unset")))
		{
			while (mini->exe[++i])
			{
				flag = unset_var(mini->env, mini->exe[i]);
				if (flag == 1)
					mini->old_ret = 1;
			}
		}
		else
			return (recover_cmd_part_2(mini));
	}
	else
		return (2);
	return (1);
}
