/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:57:37 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/27 10:44:41 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *msg, int retur)
{
	write(2, "MINISHELL : ", 12);
	write(2, msg, ft_strlen(msg));
	return (retur);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;

	if (ac != 1)
		return (print_error("TOO MUCH ARG", -1));
	(void)av;
	(void)envp;
	while (42)
	{
		str = readline("> ");
		if (lexer(str, envp) == -1)
			return (-1);
		free(str);
	}
	return (0);
}
