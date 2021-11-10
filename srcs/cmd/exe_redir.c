/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:16:58 by elisehautef       #+#    #+#             */
/*   Updated: 2021/11/10 15:52:22 by ehautefa         ###   ########.fr       */
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
		if (file_fd == -1)
			return (print_error("OPEN FAILED\n", -1, 1));
		while (read(file_fd, str, PAGE_SIZE) == PAGE_SIZE)
			;
		free(str);
	}
	if (dup2(file_fd, red->n) == -1 || close(file_fd) == -1)
		return (print_error("DUP FAILED\n", -1, 1));
	return (red->save_fd);
}

int	do_left_redir(t_redir *red)
{
	int	file_fd;

	red->save_fd = dup(red->n);
	file_fd = open(red->path, O_RDONLY);
	if (file_fd == -1)
		return (print_error("OPEN FAILED\n", -1, 1));
	if (dup2(file_fd, red->n) == -1 || close(file_fd) == -1)
		return (print_error("DUP FAILED\n", -1, 1));
	return (0);
}

int	close_fd(t_redir *red, int count)
{
	int	i;

	i = count - 1;
	while (i >= 0)
	{
		if (red && red[i].save_fd && red[i].save_fd == -1)
			close(red[i].n);
		else if (red && red[i].save_fd)
		{
			dup2(red[i].save_fd, red[i].n);
			close(red[i].save_fd);
			red[i].save_fd = -1;
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
	if (ret == 2)
		return (0);
	return (ret);
}

int	exe_redir(t_redir *red, int count, int pipe_flag)
{
	int		i;

	if (pipe_flag == 0 && exe_here_doc(red, count) == -1)
		return (-1);
	i = -1;
	while (++i < count)
	{
		if (red[i].op[0] == '>')
		{
			if (do_right_redir(&red[i]) == -1)
			{
				close_fd(red, i);
				return (-2);
			}
		}
		else if (red[i].op[1] == '\0')
		{
			if (do_left_redir(&red[i]) == -1)
			{
				close_fd(red, i);
				return (-2);
			}
		}
	}
	return (0);
}
