/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:32:54 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/20 18:10:07 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_value(t_env *env, char **value)
{
	int		i; 
	t_env	*tmp;
	int		size;

	i = 0;
	tmp = env;
	while (env)
	{
		if (!ft_strcmp("PWD", env->name))
			size = ft_strlen(env->value);
		env = env->next;
	}
	*value = malloc(sizeof(char) * size + 1);
	if (!value)
		return (-1);
	size = 0;
	while (tmp)
	{
		if (!ft_strcmp("PWD", tmp->name))
		{
			while (tmp->value[i])
				(*value)[size++] = tmp->value[i++];
		}
		tmp = tmp->next;
	}
	(*value)[size] = '\0';
	return (0);
}

int	change_directory(t_env *env, char *cmd)
{
	char	*tmp_path;
	char	*pwd;

	pwd = NULL;
	tmp_path = malloc(sizeof(char) * 1000);
	if (!tmp_path)
		return (-1);
	if (search_value(env, &pwd) != 0)
		return (-1);
	if (chdir(cmd) == -1)
		printf("PATH NOT FOUND\n");
	else
	{
		while (env)
		{
			if (!ft_strcmp(env->name, "PWD"))
			{
				tmp_path = getcwd(tmp_path, 1000);
				if (!tmp_path)
					return (-1);
				change_exp_value(env, "PWD", tmp_path);
				change_exp_value(env, "OLDPWD", pwd);
			}
			env = env->next;
		}
	}
	return (0);
}