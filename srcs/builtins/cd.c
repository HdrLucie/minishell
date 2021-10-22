/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:32:54 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/22 18:54:27 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_value(t_env *env, char **value, char *to_find)
{
	int		i;
	t_env	*tmp;
	int		size;

	i = 0;
	tmp = env;
	while (env)
	{
		if (!ft_strcmp(to_find, env->name))
			size = ft_strlen(env->value);
		env = env->next;
	}
	*value = malloc(sizeof(char) * size + 1);
	if (!value)
		return (-1);
	size = 0;
	while (tmp)
	{
		if (!ft_strcmp(to_find, tmp->name))
		{
			while (tmp->value[i])
				(*value)[size++] = tmp->value[i++];
		}
		tmp = tmp->next;
	}
	(*value)[size] = '\0';
	return (0);
}

int	next_simple_cd(t_env *env, char *path, char *pwd, char *oldpwd)
{
	int	i;

	i = 0;
	while (path[i] && path[i] == ' ')
		i++;
	if (path[i] == '-')
	{
		change_exp_value(env, "OLDPWD", pwd);
		change_exp_value(env, "PWD", oldpwd);
		printf("%s\n", pwd);
		return (0);
	}
	if (path[i] == '/' && path[i + 1] == '\0')
	{
		change_exp_value(env, "OLDPWD", pwd);
		while (env)
		{
			if (!ft_strcmp("PWD", env->name))
			{
				env->value[0] = '/';
				env->value[1] = '\0';
				return (0);
			}
			env = env->next;
		}
	}
	return (1);
}

int	simple_change_directory(t_env *env, char *path)
{
	char	*home;
	char	*pwd;
	char	*oldpwd;
	int		i;

	i = 0;
	home = NULL;
	oldpwd = NULL;
	pwd = NULL;
	if ((search_value(env, &home, "HOME") != 0
			|| search_value(env, &pwd, "PWD") != 0
			|| search_value(env, &oldpwd, "OLDPWD") != 0))
		return (-1);
	if (!path)
	{
		change_exp_value(env, "OLDPWD", pwd);
		change_exp_value(env, "PWD", home);
		return (0);
	}
	if (next_simple_cd(env, path, pwd, oldpwd) == 0)
		return (0);
	return (1);
}

int	relative_change_directory(t_env *env, char *cmd)
{
	char	*tmp_path;
	char	*pwd;

	pwd = NULL;
	tmp_path = malloc(sizeof(char) * 1000);
	if (!tmp_path)
		return (-1);
	if (search_value(env, &pwd, "PWD") != 0)
		return (-1);
	if (chdir(cmd) == -1)
		printf("PATH NOT FOUND\n");
	else
	{
		tmp_path = getcwd(tmp_path, 1000);
		if (!tmp_path)
			return (-1);
		change_exp_value(env, "OLDPWD", pwd);
		change_exp_value(env, "PWD", tmp_path);
	}
	return (0);
}

int	change_directory(t_env *env, char *cmd)
{
	if (simple_change_directory(env, cmd) == 0)
		return (0);
	else if (simple_change_directory(env, cmd) == -1)
		return (-1);
	if (relative_change_directory(env, cmd) == 0)
		return (0);
	else
		return (-1);
}
