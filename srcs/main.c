/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:57:37 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/02 16:01:27 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *msg, int retur)
{
	write(2, "MINISHELL : ", 12);
	write(2, msg, ft_strlen(msg));
	return (retur);
}

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
	{
		printf("%s\n", strs[i]);
		free(strs[i]);
	}
	free(strs);
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
		add_history(str);
		if (lexer(str, envp) == -1)
			return (-1);
		free(str);
	}
	rl_clear_history();
	return (0);
}
