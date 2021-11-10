/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:59:12 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/10 16:23:28 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_fd(char *cmd)
{
	int	fd;

	if (cmd[0] == '>')
		fd = 1;
	else if (cmd[0] == '<')
		fd = 0;
	else if (ft_isdigit(cmd[0]))
		fd = cmd[0] - '0';
	else
		fd = -1;
	return (fd);
}

int	parse_op(char *cmd, char *op)
{
	int	i;

	if (cmd && cmd[0] && is_redir(cmd[0]))
		i = 0;
	else if (cmd && cmd[1] && is_redir(cmd[1]))
		i = 1;
	else
		return (-1);
	op[0] = cmd[i];
	if (cmd[i + 1] && cmd[i] == cmd[i + 1])
	{
		op[1] = cmd[i + 1];
		op[2] = '\0';
	}
	else if (cmd[i + 1] && cmd[i] != cmd[i + 1])
		return (-1);
	else
		op[1] = '\0';
	return (0);
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
	red[j].n = parse_fd(cmd[i]);
	if (parse_op(cmd[i], red[j].op) == -1)
		return (print_error("PARSE ERROR REDIR\n", -2, 2));
	if (cmd[i + 1])
		red[j].path = ft_strdup(cmd[i + 1]);
	if (!cmd[i + 1] || valid_path(red[j].path))
		return (print_error("PARSE ERROR REDIR\n", -2, 2));
	i++;
	return (i);
}

int	redir(char **exe, t_mini *mini)
{
	int	ret;

	ret = 0;
	mini->nb_red = count_redir(exe);
	mini->red = malloc(mini->nb_red * sizeof(t_redir));
	if (mini->red == NULL)
		return (print_error("ALLOCATION FAILED\n", -1, errno));
	mini->exe = malloc(sizeof(char *) * (ft_strslen(exe) + 1));
	if (mini->exe == NULL)
		return (print_error("ALLOCATION FAILED\n", -1, errno));
	ret = fill_red(exe, mini->red, mini->exe);
	mini->exe = remove_quote(mini->exe);
	if (ret < 0)
	{
		mini->old_ret = ret;
		return (quit_red(mini, ret, NULL));
	}
	ret = exe_redir(mini->red, mini->nb_red, 0);
	if (ret < 0)
		return (quit_red(mini, ret, NULL));
	ret = exe_cmd(mini);
	return (quit_red(mini, ret, NULL));
}
