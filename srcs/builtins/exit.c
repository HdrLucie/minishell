/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:49:24 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/07 16:05:32 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_env *env, t_cmd *cmd)
{
	t_env	*tmp;

	tmp = env;
	printf("EXIT : %s\n", env->name);
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
	env = NULL;
	exit(0);
}
