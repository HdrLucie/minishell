/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:59:12 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/12 13:59:51 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc_strs(char **strs, size_t size)
{
	char	**res;
	size_t	i;

	i = 0;
	res = malloc((size + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (strs[i] && i < size)
	{
		res[i] = ft_strdup(strs[i]);
		i++;
	}
	res[size - 1] = NULL;
	free_strs(strs);
	return (res);
}

int	fill_red(char **cmd, t_redir *red, char **exe)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i][0] && (is_redir(cmd[i][0])
			|| (ft_isdigit(cmd[i][0]) && cmd[i][1] && is_redir(cmd[i][1]))))
		{
			i = parse_redir(cmd, i, red, j);
			if (i < 0)
			{
				exe[k] = NULL;
				return (i);
			}
			j++;
		}
		else
			exe[k++] = ft_strdup(cmd[i]);
		i++;
	}
	exe[k] = NULL;
	return (0);
}

void	print_redir(t_redir	*red, int count, char **cmd)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("RED : %d\n", i);
		printf("n: %d\n", red[i].n);
		printf("op: %s\n", red[i].op);
		printf("path: %s\n", red[i].path);
		i++;
	}
	i = 0;
	printf("CMD : \n");
	while (cmd && cmd[i])
	{
		printf("%s\n", cmd[i]);
		i++;
	}
}

int	count_redir(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i][0] && (is_redir(cmd[i][0])
			|| (ft_isdigit(cmd[i][0]) && cmd[i][1] && is_redir(cmd[i][1]))))
		{
			count++;
			i++;
		}
		if (cmd[i])
			i++;
	}
	return (count);
}

void	free_red(t_redir *red, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (red && &red[i] && red[i].path)
			free (red[i].path);
		i++;
	}
	free(red);
	red = NULL;
}
 