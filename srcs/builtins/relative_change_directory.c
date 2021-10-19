/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_change_directory.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:29:26 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/19 19:26:25 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	relative_path(t_env *env, char *path, char **pwd, char **oldpwd)
{
	int		i;
	char	*tmp_path;
	int		size;

	i = 0;
	size = 0;
	tmp_path = NULL;
	(void)oldpwd;
	(void)env;
	(void)pwd;
	printf("%s\n", path);
	if (malloc_tmp_path(path, &tmp_path, ft_strlen(path)) != 0)
		return (-1);
	while (tmp_path[i] && tmp_path[i] == ' ')
		i++;
	while (tmp_path[i])
	{
		if ((tmp_path[i] == '.' && tmp_path[i + 1] == '.')
		|| (tmp_path[i] == '.' && tmp_path[i + 1] == '.' && tmp_path[i + 2] == '/'))
		{
			size = check_last_slash(tmp_path);
			printf("SIZE %d", size);
			malloc_tmp_path(path, &tmp_path, size);
			printf("PATH %s", tmp_path);
		}
		i++;
	}
	if (!chdir(tmp_path))
		printf("PATH NOT FOUND\n");
	else
	{
		while (env)
		{
			if (!ft_strcmp(env->name, "PWD"))
			{
				change_exp_value(env, "PWD", tmp_path);
				change_exp_value(env, "OLDPWD", *pwd);
			}
			env = env->next;
		}
	}
	return (0);
}