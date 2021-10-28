/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:25:52 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/28 17:30:34 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Retours d'erreurs : -1, arret du programme.
**					   -2, erreur, mais le process continue. 
*/

int	fill_env_lst_value(char *str, t_env *env, int i)
{
	int	k;
	int	j;

	j = 1;
	k = i + 1;
	while (str[++i])
		j++;
	env->value = malloc(sizeof(char) * j + 1);
	if (!env->value)
		return (-1);
	j = 0;
	while (str[k])
	{
		if (!ft_strcmp("SHLVL", env->name))
		{
			if (env->value)
				free(env->value);
			env->value = ft_itoa(ft_atoi(&str[k]) + 1);
			return (0);
		}
		else
			env->value[j] = str[k];
		j++;
		k++;
	}
	env->value[j] = '\0';
	return (0);
}

int	fill_env_lst_name(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	env->name = malloc(sizeof(char) * i + 1);
	if (!env->name)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		env->name[i] = str[i];
		i++;
	}
	env->name[i] = '\0';
	if (fill_env_lst_value(str, env, i) == -1)
		return (-1);
	return (0);
}

t_env	*create_env_lst(char **env)
{
	t_env	*env_lst;
	t_env	*current_node;
	int		i;

	i = 0;
	env_lst = NULL;
	current_node = NULL;
	while (env[i])
	{
		current_node = malloc(sizeof(t_env));
		if (!current_node)
			return (NULL);
		current_node->next = NULL;
		current_node->next_alpha = NULL;
		lstadd_back_env(&env_lst, current_node);
		if (fill_env_lst_name(env[i], current_node) == -1)
			return (NULL);
		i++;
	}
	return (env_lst);
}
