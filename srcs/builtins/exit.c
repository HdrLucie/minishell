/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:49:24 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/12 19:39:59 by hlucie           ###   ########.fr       */
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
	printf("exit\n");
	exit(0);
}
