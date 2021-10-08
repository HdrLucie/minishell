/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:59:12 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/08 10:05:58 by elisehautef      ###   ########.fr       */
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
	printf("COUNT RED : %d\n", count);
	return (count);
}

int	parse_redir(char **cmd, int i, t_redir red)
{
	if (cmd[i][0] == '>')
		red.n = 1;
	else
		red.n = 0;
	red.op[0] = cmd[i][0];
	if (i > 0 && cmd[i - 1] && ft_strlen(cmd[i - 1]) == 1
		&& cmd[i - 1][0] >= '0' && cmd[i - 1][0] <= '9')
		red.n = cmd[i - 1][0] - '0';
	if (cmd[i + 1] && ft_strlen(cmd[i + 1]) == 1
		&& cmd[i + 1][0] == cmd[i][0])
	{
		red.op[1] = '>';
		red.op[2] = '\0';
		if (cmd[i + 2])
			red.path = ft_strdup(cmd[i + 2]);
		else
			return (print_error("PARSE ERROR\n", -1));
		i += 2;
	}
	else
	{
		red.op[1] = '\0';
		if (cmd[i + 1])
			red.path = ft_strdup(cmd[i + 1]);
		else
			return (print_error("PARSE ERROR\n", -1));
		i++;
	}
	return (i);
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
		if (ft_strcmp(">", cmd[i]) == 0 || ft_strcmp("<", cmd[i]) == 0)
		{
			i = parse_redir(cmd, i, red[j]);
			if (i == -1)
				return (-1);
			j++;
		}
		else
			if (!cmd[i + 1] || (ft_strcmp(cmd[i + 1], "<")
					&& ft_strcmp(cmd[i + 1], ">")) || ft_strlen(cmd[i]) != 1
				|| cmd[i][0] < '0' || cmd[i][0] > '9')
				exe[k++] = ft_strdup(cmd[i]);
		i++;
	}
	exe[k] = NULL;
	return (0);
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

char	**redir(char **cmd)
{
	int		count;
	t_redir	*red;
	char	**exe;

	count = count_redir(cmd);
	red = malloc(count * sizeof(t_redir));
	if (red == NULL)
		return (print_char_error("ALLOCATION FAILED\n", -1));
	exe = malloc(sizeof(char *) * (ft_strslen(cmd) + 1));
	if (exe == NULL)
		return (print_char_error("ALLOCATION FAILED\n", -1));
	if (fill_red(cmd, red, exe) == -1)
		return (NULL);
	// print_redir(red, count, exe);
	free_red(red, count);
	return (exe);
}
