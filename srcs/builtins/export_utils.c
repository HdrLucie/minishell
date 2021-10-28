/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:50:37 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/28 19:44:13 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_first_alpha_node(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env)
	{
		if (env->first_alpha_node == 1)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	check_export_value(char **var_export)
{
	int	i;

	i = 1;
	while (var_export[i])
	{
		if (ft_isdigit(var_export[i][0]) == 1)
		{
			printf("bash: export: `%c': not a valid identifier\n",
				var_export[i][0]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	change_exp_value(t_env *env, char *name_exp, char *value_exp)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strcmp(env->name, name_exp))
			env = env->next;
		else
		{
			if (env->value)
				free(env->value);
			env->value = value_exp;
			return (0);
		}
	}
	return (1);
}

int	is_in_env(t_env *env, char *var_export)
{
	while (env)
	{
		if (ft_strcmp(env->name, var_export))
			env = env->next;
		else
			return (1);
	}
	return (0);
}
