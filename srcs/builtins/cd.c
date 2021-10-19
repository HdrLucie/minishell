/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:32:54 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/19 16:33:18 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_directory(t_env *env, char **directory, char *to_find)
{
	int		i;
	int		size;
	t_env	*tmp;

	i = 0;
	size = 0;
	tmp = env;
	while (env)
	{
		if (!ft_strcmp(env->name, (to_find)))
			size = ft_strlen(env->value);
		env = env->next;
	}
	*directory = malloc(sizeof(char) * size + 1);
	if (!directory)
		return (-1);
	size = 0;
	env = tmp;
	while (env)
	{
		if (!ft_strcmp(env->name, to_find))
		{
			while (env->value[i])
				(*directory)[size++] = env->value[i++];
		}
		env = env->next;
	}
	(*directory)[i] = '\0';
	return (1);
}

int	check_last_slash(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0)
	{
		if (str[i] == '/' && i != 0)
			return (i);
		i--;
	}
	return (0);
}

int	previous_directory(t_env *env)
{
	char	*pwd;
	int		size;
	int		i = 0;
	int		j = 0;
	t_env	*tmp;

	tmp = env;
	malloc_directory(env, &pwd, "PWD");
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
		{
			size = check_last_slash(env->value);
			change_exp_value(env, "OLDPWD", pwd);
		}
		env = env->next;
	}
	if (size == 0)
		size = 1;
	pwd = malloc(sizeof(char) * size + 1);
	env = tmp;
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
		{
			while (size > 0)
			{
				pwd[j++] = env->value[i++];
				size--; 
			}
			pwd[j] = '\0';
			change_exp_value(env, "PWD", pwd);
		}
		env = env->next;
	}
	return (1);
}

char	*search_value(t_env *env, char *to_find)
{
	while (env)
	{
		if (!ft_strcmp(env->name, to_find))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	recover_path_directory(char **home, char **pwd, char **oldpwd, t_env *env)
{
	if (!malloc_directory(env, home, "HOME"))
		return (-1);
	else if (!malloc_directory(env, oldpwd, "OLDPWD"))
		return (-1);
	else if (!malloc_directory(env, pwd, "PWD"))
		return (-1);
	return (1);
}

int	change_directory(t_env *env, char *cmd)
{
	int		i;
	char	*home;
	char	*oldpwd;
	char	*pwd;

	i = 0;
	home = NULL;
	oldpwd = NULL;
	pwd = NULL;
	if (!recover_path_directory(&home, &pwd, &oldpwd, env))
		return (-1);
	if (!cmd)
	{
		change_directory_home(env, &home, &pwd);
		return (0);
	}
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '-')
		change_directory_previous(env, &pwd, &oldpwd);
	else if (cmd[i] == '~')
		change_directory_home(env, &home, &pwd);
	else if (cmd[i] == '/' && cmd[i + 1] == '\0')
		change_directory_root(env, &pwd);
	else
		relative_path(env, cmd, &pwd, &oldpwd);
	return (0);
}