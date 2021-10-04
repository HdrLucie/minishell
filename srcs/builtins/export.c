/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:28:50 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/04 11:57:09 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes_builtins.h"

t_env	*ft_change_exp_value(t_env *env, char *name_exp, char *value_exp)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if ((ft_strncmp(env->name, name_exp, ft_strlen(name_exp))))
			env = env->next;
		else
		{
			free(env->value);
			env->value = ft_strdup(value_exp);
			return (tmp);
		}
	}
	return (NULL);
}

char	*ft_parse_export_value(char *str, char *value_exp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] && str[i] != '=')
		i++;
	k = i;
	while (str[k++])
		j++;
	value_exp = malloc(sizeof(char) * j + 1);
	if (!value_exp)
		return (NULL);
	j = 0;
	while (str[i])
		value_exp[j++] = str[i++];
	value_exp[j] = '\0';
	return (value_exp);
}

char	*ft_parse_export_name(char *str, char *name_exp)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name_exp = malloc(sizeof(char) * i + 2);
	if (!name_exp)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name_exp[i] = str[i];
		i++;
	}
	
	name_exp[i] = '\0';
	return (name_exp);
}

int	ft_check_env(t_env *env, char *var_export)
{
	while (env)
	{
		if ((ft_strncmp(env->name, var_export, ft_strlen(var_export))))
			env = env->next;
		else
			return (1);
	}
	return (0);
}

int	ft_manage_env(t_env *env, char *var_export)
{
	char	*name_exp;
	char	*value_exp;

	name_exp = NULL;
	value_exp = NULL;
	name_exp = ft_parse_export_name(var_export, name_exp);
	value_exp = ft_parse_export_value(var_export, value_exp);
	if (!ft_check_env(env, name_exp))
		ft_create_export_noodle(env, var_export);
	else
		env = ft_change_exp_value(env, name_exp, value_exp);
	free(name_exp);
	free(value_exp);
	return (1);
}
