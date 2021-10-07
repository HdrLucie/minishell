/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/07 14:48:06 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_print_list(t_cmd *tmp2)
{
	int	i;
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

int	init_red(char **token, int *i, t_redir *red)
{	
	red->n = 1;
	red->op[0] = '>';
	if (token[*i - 1] && ft_strlen(token[*i - 1]) == 1
		&& token[*i - 1][0] >= '0' && token[*i - 1][0] <= '9')
		red->n = token[*i - 1][0] - '0';
	if (token[*i + 1] && ft_strlen(token[*i - 1]) == 1
		&& token[*i + 1][0] == '>')
	{
		red->op[1] = '>';
		red->op[2] = '\0';
		if (token[*i + 2])
			red->path = ft_strdup(token[*i + 2]);
		else
			return (print_error("PARSE ERROR\n", -1));
		*i = *i + 2;
	}
	else
	{
		red->op[1] = '\0';
		if (token[*i + 1])
			red->path = ft_strdup(token[*i + 1]);
		else
			return (print_error("PARSE ERROR\n", -1));
		*i = *i + 1;
	}
	return (0);
}

t_cmd	*parse_redir(t_cmd *cmd, char **token, int *begin, int *i)
{
	t_redir	red;
	t_redir	vide;
	t_cmd	*new;
	t_cmd	*last;
	char	**tmp;

	tmp = ft_substrs(&token[*begin], *i - *begin);
	if (tmp == NULL)
		return(NULL);
	vide.op[0] = '0';
	if (init_red(token, i, &red) == -1)
		return (NULL);
	last = ft_cmd_last(cmd);
	if (cmd && last->out.op[0] == '0')
		last->out = red;
	else if (!cmd)
	{
		cmd = ft_cmd_new(tmp, vide, red);
		if (cmd == NULL)
			return(NULL);
	}
	else
	{
		new = ft_cmd_new(tmp, vide, red);
		if (new == NULL)
			return(NULL);
		ft_cmd_add_back(&cmd, new);
	}
	*begin = *i;
	*i = *i + 1;
	return (cmd);
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
		if (!ft_strcmp(token[i], "|"))
		{
			cmd = parse_pipe(cmd, token, &begin, i);
			if (cmd == NULL)
				return (-2);
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
