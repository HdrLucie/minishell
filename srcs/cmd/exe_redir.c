/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:16:58 by elisehautef       #+#    #+#             */
/*   Updated: 2021/10/21 14:03:42 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_right_redir(t_redir *red)
{
	int		file_fd;
	char	*str;

	red->save_fd = dup(red->n);
	if (ft_strlen(red->op) == 1)
		file_fd = open(red->path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
	{
		str = malloc(PAGE_SIZE);
		file_fd = open(red->path, O_RDWR | O_CREAT, 0666);
		while (read(file_fd, str, PAGE_SIZE) == PAGE_SIZE)
			;
		free(str);
	}
	dup2(file_fd, red->n);
	close(file_fd);
	return (red->save_fd);
}

int	do_left_redir(t_redir *red)
{
	int	file_fd;

	red->save_fd = dup(red->n);
	file_fd = open(red->path, O_RDONLY);
	dup2(file_fd, red->n);
	close(file_fd);
	return (0);
}

int	close_fd(t_redir *red, int count)
{
	int	i;

	i = count - 1;
	while (i >= 0)
	{
		if (red[i].op[1] == '\0' || red[i].op[0] == '>')
		{
			dup2(red[i].save_fd, red[i].n);
			close(red[i].save_fd);
		}
		i--;
	}
	return (0);
}

int	exe_cmd(t_mini *mini)
{
	int	ret;

	ret = 0;
	if (mini->exe)
	{
		ret = recover_cmd(mini);
		if (mini->exe && ret == 2)
		{
			ret = execute(mini->exe, mini);
			if (ret == -1)
				return (ret);
		}
	}
	mini->envp = env_execve(mini);
	return (ret);
}

int	exe_redir(t_redir *red, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (red[i].op[0] == '>')
			do_right_redir(&red[i]);
		else if (red[i].op[1] == '\0')
			do_left_redir(&red[i]);
		i++;
	}
	return (0);
}
