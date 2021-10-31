/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:49:24 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/31 13:24:33 by elisehautef      ###   ########.fr       */
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

void	ft_exit(t_mini *mini, int flag)
{
	int	ret;

	ret = -1;
	if (mini->exe && mini->exe[1])
		ret = ft_atoi(mini->exe[1]);
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
	if (flag)
		write(2, "exit\n", 5);
	if (ret == -1 && mini->old_ret)
		exit(mini->old_ret);
	else if (ret != -1)
		exit(ret);
	else
		exit (0);
}
