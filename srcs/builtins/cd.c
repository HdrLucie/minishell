/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:32:54 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/25 15:59:57 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_simple_cd(t_env *env, char *path, char *pwd)
{
	int		i;
	char	*oldpwd;

	i = 0;
	oldpwd = NULL;
	if (search_value(env, &oldpwd, "OLDPWD") != 0)
		return (-1);
	while (path[i] && path[i] == ' ')
		i++;
	if (path[i] == '-')
	{
		change_exp_value(env, "OLDPWD", pwd);
		change_exp_value(env, "PWD", oldpwd);
		if (chdir(oldpwd) == -1)
		{
			perror("MINISHELL ");
			return (-1);
		}
		printf("%s\n", oldpwd);
		return (0);
	}
	else if (go_home(env, i, path, pwd) == 0)
		return (0);
	return (1);
}

int	simple_change_directory(t_env *env, char *path)
{
	char	*home;
	char	*pwd;
	int		i;

	i = 0;
	home = NULL;
	pwd = NULL;
	if ((search_value(env, &home, "HOME") != 0
			|| search_value(env, &pwd, "PWD") != 0))
		return (-1);
	if (!path)
	{
		change_exp_value(env, "OLDPWD", pwd);
		change_exp_value(env, "PWD", home);
		if (chdir(home) == -1)
		{
			perror("MINISHELL ");
			return (-1);
		}
		return (0);
	}
	if (next_simple_cd(env, path, pwd) == 0)
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
	{
		perror("MINISHELL ");
		return (-1);
	}
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
	int	ret;

	ret = 0;
	ret = simple_change_directory(env, cmd);
	if (ret == -1 || ret == 0)
	{
		if (ret == -1)
			return (print_error("ALLOCATION FAILED\n", -1));
		return (ret);
	}
	else
		ret = relative_change_directory(env, cmd);
	if (ret == -1)
		return (-1);
	return (ret);
}
