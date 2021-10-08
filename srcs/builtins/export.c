/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:28:50 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/08 15:43:49 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	export_quote_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*export_create_value(char *str, char *value_exp)
{
	int	i;
	int	j;
	int	k;
	int	counter_quote;

	counter_quote = 0;
	i = 0;
	j = 0;
	k = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	k = i - 1;
	while (str[k++])
	{
		if (str[k] == '\"')
			counter_quote++;
		j++;
	}
	value_exp = malloc(sizeof(char) * j - counter_quote + 1);
	if (!value_exp)
		return (NULL);
	j = 0;
	i++;
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		value_exp[j++] = str[i++];
	}
	if (value_exp[0] == '\"')
		value_exp[0] = '\0';
	value_exp[j] = '\0';
	return (value_exp);
}

char	*export_create_name(char *str, char *name_exp)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name_exp = malloc(sizeof(char) * i + 1);
	if (!name_exp)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name_exp[i] = str[i];
		i++;
	}
	name_exp[i] = '\0';
	printf("NAME : %s | Nombre char : %d\n", name_exp, i);
	return (name_exp);
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

int	export_var(t_env *env, char *var_export)
{
	char	*name_exp;
	char	*value_exp;

	name_exp = NULL;
	value_exp = NULL;
	if (!var_export)
	{
		udpate_alpha_road(env);
		return (0);
	}
	name_exp = export_create_name(var_export, name_exp);
	value_exp = export_create_value(var_export, value_exp);
	if (!check_env(env, name_exp))
		create_export_node(env, name_exp, value_exp);
	else
		change_exp_value(env, name_exp, value_exp);
	return (1);
}
