/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:23:06 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/25 13:46:59 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_here_doc(t_redir *red)
{
	int		file_fd;
	char	*str;
	char	*file;

	str = NULL;
	red->save_fd = dup(red->n);
	file_fd = open("tmp", O_RDONLY);
	while (ft_strcmp(str, red->path))
	{
		str = readline("> ");
		if (!str)
			return (-1);
		file = ft_strcat(file, str);
		free(str);
		str = NULL;
	}
	dup2(file_fd, red->n);
	close(file_fd);
	return (0);
}

// int	do_left_redir(t_redir *red)
// {
// 	int	file_fd;

// 	red->save_fd = dup(red->n);
// 	file_fd = open(red->path, O_RDONLY);
// 	dup2(file_fd, red->n);
// 	close(file_fd);
// 	return (0);
// }