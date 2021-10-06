/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:49:24 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/06 18:31:53 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	printf("EXIT : %s\n", env->name);
	if (env)
	{
		while (env)
		{
			tmp = env->next;
			ft_free_node(env);
			env = tmp;
		}
	}
	env = NULL;
	exit(0);
}
