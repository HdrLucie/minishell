/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:59:12 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/08 12:05:45 by elisehautef      ###   ########.fr       */
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
		write(1, "here\n", 6);
		res[i] = ft_strdup(strs[i]);
		i++;
	}
	res[size - 1] = NULL;
	free_strs(strs);
	return (res);
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
		if (ft_strcmp(">", cmd[i]) == 0 || ft_strcmp("<", cmd[i]) == 0)
		{
			count++;
			i++;
		}
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
		free (red[i].path);
		i++;
	}
	free(red);
}
