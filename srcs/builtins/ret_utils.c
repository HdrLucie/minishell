/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:37:24 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/12 10:55:25 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(char *pwd, char *tmp_path, char *cmd)
{
	if (check_chdir_ret(cmd) == -1)
	{
		if_free(pwd);
		if_free(tmp_path);
		return (1);
	}
	return (0);
}

int	is_oldpwd(t_env *env, char *oldpwd)
{
	if (is_in_env(env, "OLDPWD") == 0)
	{
		write(2, "MINISHELL : cd: OLDPWD not set\n", 31);
		return (-2);
	}
	if (check_chdir_ret(oldpwd) == -1)
	{
		if_free(oldpwd);
		return (-1);
	}
	return (0);
}

int	ret_simple_cd(int ret, char *pwd)
{
	if (ret == -2)
	{
		if_free(pwd);
		return (-2);
	}
	if (ret == 0)
		return (0);
	else if (ret == -1)
		return (-1);
	if_free(pwd);
	return (1);
}

int	check_chdir_ret(char *path)
{
	if (chdir(path) == -1)
	{
		perror("MINISHELL");
		return (-1);
	}
	return (0);
}

void	if_free(char *str)
{
	if (str)
		free(str);
}
