/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:42:34 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/10 12:29:33 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_path(t_env *env, char *f_path, char *sec_path, char c)
{
	if (c == '-')
	{
		if (f_path)
			change_exp_value(env, "OLDPWD", f_path);
		else
			unset_var(&env, "OLDPWD");
		if (sec_path)
		{
			write(1, sec_path, ft_strlen(sec_path));
			write(1, "\n", 1);
			change_exp_value(env, "PWD", sec_path);
		}
	}
	else
	{
		if (f_path)
			change_exp_value(env, "OLDPWD", f_path);
		if (sec_path)
			change_exp_value(env, "PWD", sec_path);
	}
}

int	check_cd(t_env *env, char *start)
{
	if (is_in_env(env, "HOME") == 0)
	{
		printf("MINISHELL: cd: HOME not set\n");
		return (1);
	}
	if (start && (ft_strcmp("cd", start) != 0))
	{
		printf("MINISHELL: %s: No such file or directory\n", start);
		return (1);
	}
	return (0);
}

int	go_home(t_env *env, int i, char *path, char *pwd)
{
	if (path[i] == '/' && path[i + 1] == '\0')
	{
		change_exp_value(env, "OLDPWD", pwd);
		while (env)
		{
			if (!ft_strcmp("PWD", env->name))
			{
				env->value[0] = '/';
				env->value[1] = '\0';
				if (chdir(env->value) == -1)
				{
					perror("MINISHELL ");
					return (-1);
				}
				return (0);
			}
			env = env->next;
		}
	}
	return (1);
}

void	fill_cd_tmp(t_env *env, char **value, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env)
	{
		if (!ft_strcmp(to_find, env->name))
		{
			while (env->value[i])
				(*value)[j++] = env->value[i++];
		}
		env = env->next;
	}
	(*value)[j] = '\0';
}

int	search_value(t_env *env, char **value, char *to_find)
{
	int		i;
	t_env	*tmp;
	size_t	size;

	i = 0;
	size = 0;
	tmp = env;
	while (env)
	{
		if (!ft_strcmp(to_find, env->name))
		{
			if (env->value == '\0')
				return (-1);
			size = ft_strlen(env->value);
		}
		env = env->next;
	}
	if (size == 0)
		return (0);
	*value = malloc(sizeof(char) * size + 1);
	if (!value)
		return (-1);
	fill_cd_tmp(tmp, value, to_find);
	return (0);
}
