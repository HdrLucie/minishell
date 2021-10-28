/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:23:06 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 18:08:23 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_file(t_redir *red)
{
	char	*str;
	char	*file;

	str = malloc(1);
	file = malloc(1);
	if (file == NULL || str == NULL)
		return (NULL);
	file[0] = '\0';
	while (ft_strcmp(str, red->path))
	{
		free(str);
		str = readline("> ");
		if (!str)
			return (NULL);
		if (ft_strcmp(str, red->path))
		{
			if (file[0] != '\0')
				file = ft_strjoin(file, "\n");
			file = ft_strjoin(file, str);
		}
		signal(SIGINT, sig_int);
	}
	free(str);
	return (file);
}

int	do_here_doc(t_redir *red)
{
	int		fd[2];
	char	*file;

	pipe(fd);
	file = init_file(red);
	if (file == NULL)
		return (-1);
	write(fd[1], file, ft_strlen(file));
	close(fd[1]);
	free(file);
	return (fd[0]);
}

int	change_fd(t_redir *red, int last, int fd)
{
	if (last != -1)
	{
		red[last].save_fd = dup(red[last].n);
		if (dup2(fd, red[last].n) == -1)
			return (print_error(strerror(errno), -1));
		close(fd);
	}
	return (0);
}

int	exe_here_doc(t_redir *red, int count)
{
	int	i;
	int	last;
	int	fd;

	i = -1;
	last = -1;
	while (++i < count)
	{
		if (red[i].op[0] == '<' && red[i].op[1] == '<')
		{
			if (fd)
				close(fd);
			fd = do_here_doc(&red[i]);
			if (fd == -1)
				return (-1);
			last = i;
		}
	}
	return (change_fd(red, last, fd) == -1);
}
