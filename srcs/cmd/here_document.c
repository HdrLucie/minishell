/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:23:06 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/25 16:06:51 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_here_doc(t_redir *red)
{
	int		file_fd;
	char	*str;
	char	*file;

	str = malloc(1);
	if (str == NULL)
		return (-1);
	file = malloc(1);
	if (file == NULL)
		return (-1);
	red->save_fd = dup(red->n);
	file_fd = open("tmp", O_RDONLY);
	while (ft_strcmp(str, red->path))
	{
		free(str);
		str = readline("> ");
		if (!str)
			return (-1);
		if (ft_strcmp(str, red->path))
		{
			file = ft_strjoin(file, "\n");
			file = ft_strjoin(file, str);
		}
		printf("FILE : %s // STR : %s\n", file, str);
	}
	write(file_fd, file, ft_strlen(file));
	free(file);
	dup2(file_fd, red->n);
	close(file_fd);
	return (0);
}
