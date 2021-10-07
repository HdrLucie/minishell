/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/07 17:32:34 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_list(t_cmd *tmp2)
{
	int		i;
	t_cmd	*tmp;

	tmp = tmp2;
	while (tmp)
	{
		i = -1;
		printf("CMD : \n");
		while (tmp->cmd && tmp->cmd[++i])
			printf("cmd : %s\n", tmp->cmd[i]);
		tmp = tmp->next;
		printf("\n");
	}
}

int	parser(char **token, char **envp, t_env **env_lst)
{
	int		i;
	t_cmd	*cmd;
	int		begin;

	cmd = NULL;
	i = -1;
	begin = 0;
	while (token[++i])
	{
		if (!ft_strcmp(token[i], "|"))
		{
			cmd = parse_pipe(cmd, token, &begin, i);
			if (cmd == NULL)
				return (-2);
		}
	}
	if (begin != ft_strslen(token))
		cmd = parse_end(cmd, token, &begin, i);
	free_strs(token);
	ft_execute_cmd(cmd, envp, env_lst);
	return (0);
}

int	lexer(char *str, char **envp, t_env **env_lst)
{
	char	**token;
	int		ret;

	token = ft_split_quote(str);
	if (token == NULL && errno == -1)
		return (print_error("ALLOCATION FAILED\n", -1));
	else if (token == NULL)
		return (-2);
	ret = parser(token, envp, env_lst);
	if (ret == -1)
		return (ret);
	return (ret);
}
