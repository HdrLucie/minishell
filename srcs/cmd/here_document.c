/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:23:06 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/12 10:55:25 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exec_readline(char **str, char *file, t_redir *red)
{
	free(*str);
	signal(SIGINT, handler_in_here_doc);
	str[0] = readline("\033[1m\033[31m> \033[0m");
	if (g_flag_fork > 1)
	{
		dup2(g_flag_fork, 0);
		close(g_flag_fork);
		g_flag_fork = 3;
		file[0] = '\0';
		errno = -3;
		return (file);
	}
	else if (str[0] == NULL)
		write(2, "minishell: warning: here-document \
		delimited by end-of-file (wanted `EOF')\n", 74);
	if (*str && ft_strcmp(*str, red->path))
	{
		if (file[0] != '\0')
			file = ft_strjoin(file, "\n");
		file = ft_strjoin(file, *str);
	}
	return (file);
}

char	*init_file(t_redir *red)
{
	char	*str;
	char	*file;

	str = malloc(1);
	file = malloc(1);
	if (file == NULL || str == NULL)
		return (NULL);
	file[0] = '\0';
	str[0] = '\0';
	while (str && ft_strcmp(str, red->path))
	{
		file = exec_readline(&str, file, red);
	}
	if (file[0] != '\0')
		file = ft_strjoin(file, "\n");
	if (str)
		free(str);
	return (file);
}

int	do_here_doc(t_redir *red, char *file, int last)
{
	int		fd[2];

	pipe(fd);
	write(fd[1], file, ft_strlen(file));
	close(fd[1]);
	free(file);
	red[last].save_fd = dup(red[last].n);
	if (dup2(fd[0], red[last].n) == -1)
		return (print_error(strerror(errno), -1, errno));
	close(fd[0]);
	return (0);
}

char	*find_file_here_doc(t_redir *red, int count, int *last)
{
	int		i;
	char	*file;

	i = -1;
	file = NULL;
	while (++i < count)
	{
		if (red[i].op[0] && red[i].op[1]
			&& red[i].op[0] == '<' && red[i].op[1] == '<')
		{
			if (file)
				free(file);
			file = init_file(&red[i]);
			if (file == NULL)
			{
				errno = -1;
				return (NULL);
			}
			*last = i;
		}
	}
	return (file);
}

int	exe_here_doc(t_redir *red, int count)
{
	char	*file;
	int		last;

	file = find_file_here_doc(red, count, &last);
	if (file == NULL && errno == -1)
		return (-1);
	if (file)
	{
		if (do_here_doc(red, file, last) == -1)
			return (-1);
	}
	return (0);
}
