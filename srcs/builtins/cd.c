/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:32:54 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/13 06:02:42 by hlucie           ###   ########.fr       */
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

void	change_directory_home(t_env *env)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;

	malloc_directory(env, &home, "HOME");
	malloc_directory(env, &oldpwd, "OLDPWD");
	malloc_directory(env, &pwd, "PWD");
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
		{
			change_exp_value(env, "OLDPWD", pwd);
			change_exp_value(env, "PWD", home);
		}
		env = env->next;
	}
}

int	change_directory(t_env *env, char **cmd)
{
	char	*new_directory;
	int		i;
	int		j;

	i = 0;
	j = 2;
	new_directory = NULL;
	if (cmd[i][j] && cmd[i][j] != ' ')
		return (-1);
	while (cmd[i][j] && cmd[i][j] == ' ')
		j++;
	if (cmd[i][j] == '\0')
		change_directory_home(env);
	return (0);
}