/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_change_directory.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:29:26 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/20 16:46:25 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_final_path(char *path, char **final_path)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = ft_strlen(path);
	*final_path = malloc(sizeof(char) * size + 1);
	if (!final_path)
		return (-1);
	while(path[i])
	{
		if (path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '/')
			i +=2;
		(*final_path)[j++] = path[i++];
	}
	(*final_path)[j] = '\0';
	if ((*final_path)[0] == '\0')
	{
		(*final_path)[0] = '/';
		(*final_path)[1] = '\0';
	}
	return (0);
}

int	malloc_tmp_path(char *path, char **tmp_path, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*tmp_path = malloc(sizeof(char) * size + 1);
	if (!tmp_path)
		return (-1);
	while (size > 0)
	{
		(*tmp_path)[i++] = path[j++];
		size--;
	}
	(*tmp_path)[i] = '\0';
	return (0);
}

int	relative_path(t_env *env, char *path, char **pwd)
{
	int		size;
	int		i;
	char	*tmp_path;
	char	*final_path;

	i = 0;
	size = 0;
	tmp_path = NULL;
	final_path = NULL;
	if (malloc_tmp_path(path, &tmp_path, ft_strlen(path)) != 0)
		return (-1);
	while (tmp_path[i] && tmp_path[i] == ' ')
		i++;
	while (tmp_path[i])
	{
		if ((tmp_path[i] == '.' && tmp_path[i + 1] == '.' && tmp_path[i + 2] == '\0')
		|| (tmp_path[i] == '.' && tmp_path[i + 1] == '.' && tmp_path[i + 2] == '/'
		&& tmp_path[i + 3] == '\0'))
		{
			size = check_last_slash(*pwd);
			malloc_tmp_path(*pwd, &tmp_path, size);			
		}
		else if ((tmp_path[i] == '.' && tmp_path[i + 1] == '.')
		|| (tmp_path[i] == '.' && tmp_path[i + 1] == '.' && tmp_path[i + 2] == '/'))
		{
			size = check_last_slash(tmp_path);
			malloc_tmp_path(path, &tmp_path, size);
		}
		i++;
	}
	if (chdir(tmp_path) == -1)
		printf("PATH NOT FOUND\n");
	else
	{
		if (parse_final_path(tmp_path, &final_path) != 0)
			return (-1);
		while (env)
		{
			if (!ft_strcmp(env->name, "PWD"))
			{
				change_exp_value(env, "PWD", final_path);
				change_exp_value(env, "OLDPWD", *pwd);
			}
			env = env->next;
		}
	}
	// free(tmp_path);
	return (0);
}