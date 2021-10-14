/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:49:24 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/14 09:39:46 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_env *env, t_cmd *cmd, char **exe)
{
	t_env	*tmp;

	tmp = env;
	ft_cmd_clear(cmd);
	if (env)
	{
		while (env)
		{
			tmp = env->next;
			free_node(env);
			env = tmp;
		}
	}
	free_strs(exe);
	env = NULL;
	write(2, "exit\n", 5);
	exit(1);
}
