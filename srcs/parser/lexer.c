/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/30 09:39:38 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_quoted_new_line(char *str)
{
	int	i;
	// char *tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '\n')
			write(1, "here\n", 5);
			// ft_memcpy(&str[i], &str[i + 2], ft_strlen(str) - i - 2);
		i++;
	}
}

int	lexer(char *str, char **envp)
{
	char	**token;

	rm_quoted_new_line(str);
	token = ft_split_quote(str);
	if (token == NULL && errno == -1)
		return (print_error("ALLOCATION FAILED\n", -1));
	else if (token == NULL)
		return (print_error("UNCLOSED QUOTE\n", -2));
	// if (parser(token, envp) == -1)
	// 	return (-1);
	free_strs(token);
	(void)envp;
	return (0);
}
