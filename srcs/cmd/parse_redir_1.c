/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:59:12 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/29 19:41:14 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	valid_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_spe_char(str[i]) || is_redir(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	parse_redir(char **cmd, int i, t_redir *red, int j)
{
	red[j].n = parse_fd(cmd, i);
	red[j].op[0] = cmd[i][0];
	if (cmd[i + 1] && ft_strlen(cmd[i + 1]) == 1
		&& cmd[i + 1][0] == cmd[i][0])
	{
		red[j].op[1] = cmd[i][0];
		red[j].op[2] = '\0';
		i++;
	}
	else
		red[j].op[1] = '\0';
	if (cmd[i + 1])
		red[j].path = ft_strdup(cmd[i + 1]);
	if (!cmd[i + 1] || valid_path(red[j].path))
		return (print_error("PARSE ERROR\n", -1, errno));
	i++;
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

int	redir(char **exe, t_mini *mini)
{
	mini->nb_red = count_redir(exe);
	mini->red = malloc(mini->nb_red * sizeof(t_redir));
	if (mini->red == NULL)
		return (print_error("ALLOCATION FAILED\n", -1, errno));
	mini->exe = malloc(sizeof(char *) * (ft_strslen(exe) + 1));
	if (mini->exe == NULL)
		return (print_error("ALLOCATION FAILED\n", -1, errno));
	if (fill_red(exe, mini->red, mini->exe) == -1)
		return (-1);
	exe_redir(mini->red, mini->nb_red);
	exe_cmd(mini);
	write(9, mini->cmd->cmd[0], 3);
	write(9, "\n", 1);
	close_fd(mini->red, mini->nb_red);
	free_strs(mini->exe);
	free_red(mini->red, mini->nb_red);
	return (0);
}
