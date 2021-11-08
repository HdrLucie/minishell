/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:42:34 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/08 13:25:38 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_chdir_ret(char *path)
{
	if (chdir(path) == -1)
	{
		perror("MINISHELL");
		return (-1);
	}
	return (0);
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
	fill_cd_tmp(tmp, value, to_find);
	return (0);
}
