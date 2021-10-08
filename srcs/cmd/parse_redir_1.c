/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:59:12 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/08 16:01:50 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parse_fd(char **cmd, int i)
{
	int	fd;

	if (cmd[i][0] == '>')
		fd = 1;
	else
		fd = 0;
	if (i > 0 && cmd[i - 1] && ft_strlen(cmd[i - 1]) == 1
		&& cmd[i - 1][0] >= '0' && cmd[i - 1][0] <= '9')
		fd = cmd[i - 1][0] - '0';
	return (fd);
}

int	parse_redir(char **cmd, int i, t_redir *red, int j)
{
	red[j].n = parse_fd(cmd, i);
	red[j].op[0] = cmd[i][0];
	if (cmd[i + 1] && ft_strlen(cmd[i + 1]) == 1
		&& cmd[i + 1][0] == cmd[i][0])
	{
		red[j].op[1] = '>';
		red[j].op[2] = '\0';
		if (cmd[i + 2])
			red[j].path = ft_strdup(cmd[i + 2]);
		else
			return (print_error("PARSE ERROR\n", -1));
		i += 2;
	}
	else
	{
		red[j].op[1] = '\0';
		if (cmd[i + 1])
			red[j].path = ft_strdup(cmd[i + 1]);
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
			i = parse_redir(cmd, i, red, j);
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

int	redir(char **cmd, t_cmd *lst, char **envp, t_env **env_lst)
{
	int		count;
	t_redir	*red;
	char	**exe;

	count = count_redir(cmd);
	red = malloc(count * sizeof(t_redir));
	if (red == NULL)
		return (print_error("ALLOCATION FAILED\n", -1));
	exe = malloc(sizeof(char *) * (ft_strslen(cmd) + 1));
	if (exe == NULL)
		return (print_error("ALLOCATION FAILED\n", -1));
	if (fill_red(cmd, red, exe) == -1)
		return (-1);
	exe_redir(red, count);
	exe_cmd(exe, lst, envp, env_lst);
	free_strs(exe);
	close_fd(red, count);
	free_red(red, count);
	return (0);
}
