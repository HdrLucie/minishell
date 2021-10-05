/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:28:50 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/05 10:03:22 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
int	ft_change_exp_value(t_env *env, char *name_exp, char *value_exp)
=======
t_env	*ft_change_exp_value(t_env *env, char *name_exp, char *value_exp)
>>>>>>> main
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
<<<<<<< HEAD
		if (ft_strcmp(env->name, name_exp))
=======
		if ((ft_strncmp(env->name, name_exp, ft_strlen(name_exp))))
>>>>>>> main
			env = env->next;
		else
		{
			free(env->value);
<<<<<<< HEAD
			env->value = value_exp;
			return (1);
		}
	}
	return (0);
}

char	*ft_export_create_value(char *str, char *value_exp)
=======
			env->value = ft_strdup(value_exp);
			return (tmp);
		}
	}
	return (NULL);
}

char	*ft_parse_export_value(char *str, char *value_exp)
>>>>>>> main
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] && str[i] != '=')
		i++;
<<<<<<< HEAD
	if (str[i] == '\0')
		return (NULL);
	k = i + 1;
=======
	k = i;
>>>>>>> main
	while (str[k++])
		j++;
	value_exp = malloc(sizeof(char) * j + 1);
	if (!value_exp)
		return (NULL);
	j = 0;
<<<<<<< HEAD
	i++;
=======
>>>>>>> main
	while (str[i])
		value_exp[j++] = str[i++];
	value_exp[j] = '\0';
	return (value_exp);
}

<<<<<<< HEAD
char	*ft_export_create_name(char *str, char *name_exp)
=======
char	*ft_parse_export_name(char *str, char *name_exp)
>>>>>>> main
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
<<<<<<< HEAD
	name_exp = malloc(sizeof(char) * i + 1);
=======
	name_exp = malloc(sizeof(char) * i + 2);
>>>>>>> main
	if (!name_exp)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name_exp[i] = str[i];
		i++;
	}
<<<<<<< HEAD
=======
	
>>>>>>> main
	name_exp[i] = '\0';
	return (name_exp);
}

int	ft_check_env(t_env *env, char *var_export)
{
	while (env)
	{
<<<<<<< HEAD
		if (ft_strcmp(env->name, var_export))
=======
		if ((ft_strncmp(env->name, var_export, ft_strlen(var_export))))
>>>>>>> main
			env = env->next;
		else
			return (1);
	}
	return (0);
}

<<<<<<< HEAD
int	ft_export_var(t_env *env, char *var_export)
=======
int	ft_manage_env(t_env *env, char *var_export)
>>>>>>> main
{
	char	*name_exp;
	char	*value_exp;

	name_exp = NULL;
	value_exp = NULL;
<<<<<<< HEAD
	name_exp = ft_export_create_name(var_export, name_exp);
	value_exp = ft_export_create_value(var_export, value_exp);
	if (!ft_check_env(env, name_exp))
		ft_create_export_node(env, name_exp, value_exp);
	else
		ft_change_exp_value(env, name_exp, value_exp);
=======
	name_exp = ft_parse_export_name(var_export, name_exp);
	value_exp = ft_parse_export_value(var_export, value_exp);
	if (!ft_check_env(env, name_exp))
		ft_create_export_noodle(env, var_export);
	else
		env = ft_change_exp_value(env, name_exp, value_exp);
	free(name_exp);
	free(value_exp);
>>>>>>> main
	return (1);
}
