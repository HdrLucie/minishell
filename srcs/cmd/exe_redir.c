/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:16:58 by elisehautef       #+#    #+#             */
/*   Updated: 2021/10/08 17:44:23 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_right_redir(t_redir red)
{
	int	file_fd;

	red.save_fd = dup(red.n);
	if (ft_strlen(red.path) == 1)
		file_fd = open(red.path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		file_fd = open(red.path, O_WRONLY | O_CREAT, 0666);
	dup2(file_fd, red.n);
	close(file_fd);
	return (0);
}

int	do_left_redir(t_redir red)
{
	int	file_fd;

	red.save_fd = dup(red.n);
	file_fd = open(red.path, O_RDONLY);
	dup2(file_fd, red.n);
	close(file_fd);
	return (0);
}

int	close_fd(t_redir *red, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (red[i].op[1] == '\0' || red[i].op[1] == '>')
		{
			dup2(red[i].save_fd, red[i].n);
			close(red[i].save_fd);
		}
		i++;
	}
	return (0);
}

int	exe_cmd(char **exe, t_cmd *lst, char **envp, t_env **env_lst)
{
	int	ret;

	ret = 0;
	if (exe)
	{
		ret = recover_cmd(exe, env_lst, lst);
		if (exe && ret == 2)
		{
			ret = execute(exe, envp);
			if (ret == -1)
				return (ret);
		}
	}
	return (ret);
}

int	exe_redir(t_redir *red, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (red[i].op[0] == '>')
			do_right_redir(red[i]);
		else if (red[i].op[1] == '\0')
			do_left_redir(red[i]);
		i++;
	}
	return (0);
}
