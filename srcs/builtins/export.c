/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:28:50 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/12 18:19:59 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			free(env->value);
			env->value = value_exp;
			return (1);
		}
	}
	return (0);
}

void	fill_value_exp(char **value, char **cmd, int j)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while(cmd[i])
	{
		while (cmd[i][++j])
		{
			if (cmd[i][j] != '\"')
				(*value)[k++] = cmd[i][j];
		}
		j = -1;
		i++;
	}
	(*value)[k] = '\0';
}

int	recover_value_exp(char **cmd, char **value, int j)
{
	int	i;
	int	counter_l;
	int	tmp_index;

	i = 1;
	counter_l = 0;
	tmp_index = j + 1;
	while(cmd[i])
	{
		while (cmd[i][++j])
		{
			if (cmd[i][j] != '\"')
				counter_l++;
		}
		j = -1;
		i++;
	}
	*value = malloc(sizeof(char) * counter_l + 1);
	if (!value)
		return (-1);
	fill_value_exp(value, cmd, tmp_index);
	return (0);
}

int	recover_name_exp(char **cmd, char **name, char **value)
{
	int	i;
	int	j;
	int	k;
	int	counter_l;

	i = 1;
	j = -1;
	k = 0;
	counter_l = 0;
	if (!cmd[1])
		return (-2);
	while (cmd[i][++j] && cmd[i][j] != '=')
		counter_l++;
	*name = malloc(sizeof(char) * counter_l + 1);
	if (!name)
		return (-1);
	j = -1;
	while (cmd[i][++j] && cmd[i][j] != '=')
		(*name)[k++] = cmd[i][j];
	(*name)[k] = '\0';
	recover_value_exp(cmd, value, j);
	return (0);
}

int	check_env(t_env *env, char *var_export)
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

int	export_var(t_env *env, char **var_export)
{
	char	*name_exp;
	char	*value_exp;

	value_exp = NULL;
	name_exp = NULL;
	if (!var_export[1])
	{
		udpate_alpha_road(env);
		return (0);
	}
	recover_name_exp(var_export, &name_exp, &value_exp);
	if (!check_env(env, name_exp))
		create_export_node(env, name_exp, value_exp);
	else
		change_exp_value(env, name_exp, value_exp);
	return (1);
}
