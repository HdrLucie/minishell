/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:49:24 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/05 16:46:55 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_env *env)
{
	t_env	*tmp;

	tmp = env;
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
