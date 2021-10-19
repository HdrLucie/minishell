/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_change_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:57:41 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/19 16:23:43 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory_root(t_env *env, char **pwd)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
		{
			change_exp_value(env, "OLDPWD", *pwd);
			env->value[0] = '/';
			env->value[1] = '\0';
		}
		env = env->next;
	}		
}

void	change_directory_home(t_env *env, char **home, char **pwd)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
		{
			change_exp_value(env, "OLDPWD", *pwd);
			change_exp_value(env, "PWD", *home);
		}
		env = env->next;
	}
}

int	change_directory_previous(t_env *env, char **pwd, char **oldpwd)
{
	while(env)
	{
		if (!ft_strcmp(env->name, "PWD"))
		{
			change_exp_value(env, "OLDPWD", *pwd);
			change_exp_value(env, "PWD", *oldpwd);
		}
		env = env->next;
	}
	return (0);
}