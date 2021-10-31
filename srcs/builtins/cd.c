/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:32:54 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/31 19:07:28 by hlucie           ###   ########.fr       */
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
	if (path[i] == '-' && !is_in_str(path, '-', '-'))
	{
		change_exp_value(env, "OLDPWD", pwd);
		change_exp_value(env, "PWD", oldpwd);
		if (check_chdir_ret(oldpwd) == -1)
		{
			if_free(oldpwd);
			return (-1);
		}
		printf("%s\n", oldpwd);
		return (0);
	}
	if_free(oldpwd);
	if (go_home(env, i, path, pwd) == 0)
		return (0);
	return (1);
}

int	init_path(t_env *env, char **home, char **pwd)
{
	if ((search_value(env, home, "HOME") != 0
			|| search_value(env, pwd, "PWD") != 0))
	{
		if_free(*home);
		if_free(*pwd);
		return (-1);
	}
	return (0);
}

int	simple_change_directory(t_env *env, char *path)
{
	char	*home;
	char	*pwd;
	int		i;

	i = 0;
	home = NULL;
	pwd = NULL;
	if (init_path(env, &home, &pwd) == -1)
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
	if_free(home);
	if (next_simple_cd(env, path, pwd) == 0)
		return (0);
	if_free(pwd);
	return (1);
}

int	relative_change_directory(t_env *env, char *cmd)
{
	char	*tmp_path;
	char	*pwd;

	pwd = NULL;
	tmp_path = malloc(sizeof(char) * 1000);
	if (check_chdir_ret(cmd) == -1 || !tmp_path
		|| search_value(env, &pwd, "PWD") != 0)
	{
		if_free(pwd);
		if_free(tmp_path);
		return (-1);
	}
	else
	{
		tmp_path = getcwd(tmp_path, 1000);
		if (!tmp_path)
		{
			printf("MINISHELL : cd: %s: No such file or directory\n", cmd);
			return (-1);
		}
		change_exp_value(env, "OLDPWD", pwd);
		change_exp_value(env, "PWD", tmp_path);
	}
	return (0);
}

int	change_directory(t_env *env, char *start, char *cmd)
{
	int	ret;
	int	i;

	ret = 1;
	i = 0;
	if (check_cd(env, start) == 0)
		return (0);
	while (cmd && cmd[i] && ft_isalpha(cmd[i]))
		i++;
	if (!cmd || cmd[i])
		ret = simple_change_directory(env, cmd);
	if (ret == -1 || ret == 0)
	{
		if (ret == -1)
			return (-1);
		return (ret);
	}
	return (relative_change_directory(env, cmd));
}
