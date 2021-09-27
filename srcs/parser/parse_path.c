/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:45:17 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/27 18:30:39 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_strcat_parse_path(char *s1, char *s2)
{
	int		size_s1;
	int		size_s2;
	int		i;
	char	*s3;

	i = -1;
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	s3 = malloc(sizeof(char *) * (size_s1 + size_s2 + 1));
	if (s3 == NULL)
		return (NULL);
	while (++i < size_s1)
		s3[i] = s1[i];
	i--;
	while (++i < size_s1 + size_s2)
		s3[i] = s2[i - size_s1];
	s3[i] = '\0';
	return (s3);
}


int	ft_strccmp(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] != c && s2[i] != c)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == c)
		return (0);
	return (s1[i] - s2[i]);
}

char	*find_path(char **path, char *cmd)
{
	int		i;
	char	*test;
	char	*tmp;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	while (path[i])
	{
		tmp = ft_strcat_parse_path(path[i], "/");
		test = ft_strcat_parse_path(tmp, cmd);
		free(tmp);
		if (access(test, F_OK) != -1)
		{	
			free (cmd);
			return (test);
		}
		free(test);
		test = NULL;
		i++;
	}
	return (cmd);
}

int	free_path(char **path, int retur)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		path[i] = NULL;
		i++;
	}
	free(path);
	path = NULL;
	return (retur);
}

int	parse_cmd(char *cmd)
{
	char	**path;
	char	*env_path;

	env_path = getenv("PATH");
	if (env_path == NULL)
		env_path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:\
		/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
	path = ft_split(env_path, ':');
	if (path == NULL)
		return (0);
	cmd = find_path(path, cmd);
	printf("cmd : %s\n", cmd);
	return (free_path(path, 0));
}
