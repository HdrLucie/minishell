/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/06 16:21:42 by ehautefa         ###   ########.fr       */
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
		i = -1;
		while (tmp->cmd && tmp->cmd[++i])
			printf("cmd : %s\n", tmp->cmd[i]);
		if (tmp->in.op[0])
			printf("IN : %c\n", tmp->in.op[0]);
		if (tmp->out.n)
			printf("OUT : %d\n", tmp->out.n);
		if (tmp->out.op[0])
			printf("OUT : %c\n", tmp->out.op[0]);
		if (tmp->out.path)
			printf("OUT : %s\n", tmp->out.path);
		tmp = tmp->next;
		printf("\n");
	}
}

int	init_red(char **token, int *i, t_redir *red)
{	
	red->n = 1;
	red->op[0] = '>';
	if (token[*i - 1] && ft_strlen(token[*i - 1]) == 1
		&& token[*i - 1][0] >= '0' && token[*i - 1][0] >= '9')
		red->n = token[*i - 1][0] - '0';
	if (token[*i + 1] && ft_strlen(token[*i - 1]) == 1
		&& token[*i + 1][0] >= '>')
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

	write(1, "hello\n", 6);
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
		write(1, "here\n", 5);
		cmd = ft_cmd_new(tmp, vide, red);
		if (cmd == NULL)
			return(NULL);
	}
	else
	{
		write(1, "hare\n", 5);
		new = ft_cmd_new(tmp, vide, red);
		if (new == NULL)
			return(NULL);
		ft_cmd_add_back(&cmd, new);
	}
	*begin = *i;
	return (cmd);
}

t_cmd	*parse_pipe(t_cmd *cmd, char **token, int *begin, int i)
{
	char	**tmp;
	t_redir	out;
	t_redir	in;
	t_cmd	*new;
	t_cmd	*last;

	out.op[0] = '|';
	in.op[0] = '0';
	tmp = ft_substrs(&token[*begin], i - *begin);
	if (tmp == NULL)
		return(NULL);
	last = ft_cmd_last(cmd);
	if (cmd && last->cmd == NULL)
	{
		last->cmd = tmp;
		last->out = out;
	}
	else if (!cmd)
	{
		cmd = ft_cmd_new(tmp, in, out);
		if (cmd == NULL)
			return(NULL);
	}
	else
	{
		new = ft_cmd_new(tmp, in, out);
		if (new == NULL)
			return(NULL);
		ft_cmd_add_back(&cmd, new);
	}
	new = ft_cmd_new(NULL, out, in);
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
		// 	cmd = parse_redir(cmd, token, &begin, &i);
		if (!ft_strcmp(token[i], "|"))
			cmd = parse_pipe(cmd, token, &begin, i);
		i++;
	}
	// if (begin != ft_strslen(token))
	// 	cmd = parse_pipe(cmd, token, &begin, i);
	ft_execute_cmd(cmd, envp, env_lst);
	ft_print_list(cmd);
	return (0);
}

// int	replace_var(char **token, t_env *env_lst)
// {
// 	int	i;

// 	while (token && token[i])
// 	{
// 		if (token[i][0] == '$')
// 		{

// 		}
// 	}
// }

int	lexer(char *str, char **envp, t_env *env_lst)
{
	char	**token;

	token = ft_split_quote(str);
	if (token == NULL && errno == -1)
		return (print_error("ALLOCATION FAILED\n", -1));
	else if (token == NULL)
		return (-2);
	// replace_var(token, env_lst);
	if (parser(token, envp, env_lst) == -1)
		return (-1);
	free_strs(token);
	return (0);
}
