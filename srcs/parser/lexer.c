/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/06 12:03:23 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_substrs(char **s, size_t len)
{
	char		**str;
	size_t		i;
	size_t		size;

	i = -1;
	str = malloc((len + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (++i < len && s[i])
	{
		size = ft_strlen(s[i]);
		str[i] = malloc((size + 1) * sizeof(char));
		if (str[i] == NULL)
			return (NULL);
		ft_strlcpy(str[i], s[i], size + 1);
	}
	str[i] = NULL;
	return (str);
}

void ft_print_list(t_cmd *tmp2)
{
	int	i;
	t_cmd	*tmp;

	tmp = tmp2;
	while (tmp)
	{
		if (tmp->cmd)
		{
			i = -1;
			while (tmp->cmd[++i])
				printf("cmd : %s\n", tmp->cmd[i]);
		}
		// if (tmp->in->op[0])
		// 	printf("IN : %c\n", tmp->in->op[0]);
		// if (tmp->out->op[0])
		// 	printf("OUT : %c\n", tmp->out->op[0]);
		tmp = tmp->next;
		printf("\n");
	}
}

t_cmd	*parse_pipe(t_cmd *cmd, char **token, int *begin, int i)
{
	char	**tmp;
	t_redir	out;
	t_redir	in;
	t_cmd	*new;

	out.op[0] = '|';
	in.op[0] = '|';
	tmp = ft_substrs(&token[*begin], i - *begin);
	if (tmp == NULL)
		return(NULL);
	if (cmd && cmd->cmd == NULL)
	{
		cmd->cmd = tmp;
		cmd->out = &out;
	}
	else if (!cmd)
	{
		cmd = ft_cmd_new(tmp, (t_redir *)0, &out);
		if (cmd == NULL)
			return(NULL);
	}
	else
	{
		new = ft_cmd_new(tmp, (t_redir *)0, &out);
		if (new == NULL)
			return(NULL);
		ft_cmd_add_back(&cmd, new);
	}
	new = ft_cmd_new(NULL, &in, (t_redir *)0);
	if (new == NULL)
		return(NULL);
	ft_cmd_add_back(&cmd, new);
	*begin = i + 1;
	return (cmd);
}

int	parser(char **token, char **envp, t_env *env_lst)
{
	int		i;
	t_cmd	*cmd;
	int		begin;

	cmd = NULL;
	i = 0;
	begin = 0;
	(void)envp;
	(void)env_lst;
	while (token[i])
	{
		// if(!ft_strcmp(token[i], ">") || !ft_strcmp(token[i], "<"))
		// 	parse_redir(cmd, token, &begin);
		if (!ft_strcmp(token[i], "|"))
			cmd = parse_pipe(cmd, token, &begin, i);
		i++;
	}
	ft_print_list(cmd);
	return (0);
}

int	lexer(char *str, char **envp, t_env *env_lst)
{
	char	**token;

	token = ft_split_quote(str);
	if (token == NULL && errno == -1)
		return (print_error("ALLOCATION FAILED\n", -1));
	else if (token == NULL)
		return (-2);
	if (parser(token, envp, env_lst) == -1)
		return (-1);
	free_strs(token);
	return (0);
}
