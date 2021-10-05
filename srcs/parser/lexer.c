/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/05 09:52:47 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char *str, char **envp, t_env *env_lst)
{
	char	**token;

	token = ft_split_quote(str);
	if (token == NULL && errno == -1)
		return (print_error("ALLOCATION FAILED\n", -1));
	else if (token == NULL)
		return (-2);
	if (fill_cmd(token, envp, env_lst) == -1)
		return (-1);
	free_strs(token);
	return (0);
}
