/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:59:12 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/07 18:21:42 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir(t_redir	*red, int count)
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
}

int	count_redir(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
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

int	fill_red(char **cmd, t_redir *red)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (ft_strcmp(">", cmd[i]) == 0 || ft_strcmp("<", cmd[i]) == 0)
		{
			if (cmd[i][0] == '>')
				red[j].n = 1;
			else
				red[j].n = 0;
			red[j].op[0] = cmd[i][0];
			if (cmd[i - 1] && ft_strlen(cmd[i - 1]) == 1
				&& cmd[i - 1][0] >= '0' && cmd[i - 1][0] <= '9')
				red[j].n = cmd[i - 1][0] - '0';
			if (cmd[i + 1] && ft_strlen(cmd[i + 1]) == 1
				&& cmd[i + 1][0] == cmd[i][0])
			{
				red[j].op[1] = '>';
				red[j].op[2] = '\0';
				if (cmd[i + 2])
					red[j].path = ft_strdup(cmd[i + 2]);
				else
					return (print_error("PARSE ERROR\n", -1));
				i++;
			}
			else
			{
				red[j].op[1] = '\0';
				if (cmd[i + 1])
					red[j].path = ft_strdup(cmd[i + 1]);
				else
					return (print_error("PARSE ERROR\n", -1));
			}
			j++;	
		}
		i++;
	}
	return (0);
}


int	redir(char **cmd)
{
	int		count;
	t_redir	*red;

	count = count_redir(cmd);
	red = malloc(count * sizeof(t_redir));
	if (red == NULL)
		return (print_error("ALLOCATION FAILED\n", -1));
	if (fill_red(cmd, red) == -1)
		return (-1);
	// print_redir(red, count);
	free(red);
	return (0);
}