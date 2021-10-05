/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:57:37 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/05 09:52:45 by ehautefa         ###   ########.fr       */
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
	t_env	*env_lst;

	if (ac != 1)
		return (print_error("TOO MUCH ARG", -1));
	(void)av;
	env_lst = create_env_lst(envp);
	while (42)
	{
		str = readline("> ");
		add_history(str);
		if (lexer(str, envp, env_lst) == -1)
			return (-1);
		free(str);
	}
	rl_clear_history();
	return (0);
}
