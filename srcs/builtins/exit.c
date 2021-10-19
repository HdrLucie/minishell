/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:49:24 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/19 12:34:07 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free_node(env);
		env = tmp;
	}
	env = NULL;
}

void	ft_exit(t_mini *mini)
{
	if (mini->cmd)
		ft_cmd_clear(mini->cmd);
	if (mini->env)
		free_env(*mini->env);
	if (mini->exe)
		free_strs(mini->exe);
	if (mini->envp && mini->f_envp)
		free_strs(mini->envp);
	if (mini->red)
		free_red(mini->red, mini->nb_red);
	write(2, "exit\n", 5);
	exit(1);
}
