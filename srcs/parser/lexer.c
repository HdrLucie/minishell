/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/27 12:49:14 by ehautefa         ###   ########.fr       */
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
		if (tmp->pipe_in)
			printf("INA : 0 : %d 1: %d\n", tmp->pipe_in[0], tmp->pipe_in[1]);
		if (tmp->pipe_out)
			printf("OUT : 0 : %d 1: %d\n", tmp->pipe_out[0], tmp->pipe_out[1]);
		tmp = tmp->next;
		printf("\n");
	}
}

// int	*create_pipe(void)
// {
// 	int fd[2];

// 	if (pipe(fd) == -1)
// 	{
// 		perror("MINISHELL ");
// 		return (NULL);
// 	}
// 	return (fd);
// }

int	init_pipe(t_mini *mini)
{
	t_cmd	*tmp;
	int		f_begin;
	int		*fd;
	
	f_begin = 1;
	tmp = mini->cmd;
	tmp->pipe_in = NULL;
	tmp->pipe_out = NULL;
	while (tmp)
	{
		if (f_begin)
			f_begin = 0;
		if (tmp->next)
		{
			fd = malloc(2 * sizeof(int));
			if (fd == NULL)
				return (-1);
			if (pipe(fd) == -1)
			{
				perror("MINISHELL ");
				return (-1);
			}
			
			tmp->pipe_out = fd;
			tmp->next->pipe_in = fd;
			printf("INIT : 0 : %d 1: %d\n", tmp->pipe_out[0], tmp->pipe_out[1]);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	parser(char **token, t_mini *mini)
{
	int		i;
	int		begin;

	mini->cmd = NULL;
	i = -1;
	begin = 0;
	while (token[++i])
	{
		if (!ft_strcmp(token[i], "|"))
		{
			mini->cmd = parse_pipe(mini->cmd, token, &begin, i);
			if (mini->cmd == NULL)
				return (-2);
		}
	}
	if (begin != ft_strslen(token))
		mini->cmd = parse_end(mini->cmd, token, &begin, i);
	free_strs(token);
	if (init_pipe(mini))
		return (-1);
	ft_execute_cmd(mini);
	ft_cmd_clear(mini->cmd);
	return (0);
}

int	lexer(char *str, t_mini *mini)
{
	char	**token;
	int		ret;

	token = ft_split_dollar(str);
	if (token == NULL)
		return (-1);
	token = expand_var_env(token, mini->env, mini->old_ret);
	if (token == NULL)
		return (-1);
	token = ft_split_quote(ft_reverse_split(token));
	if (token == NULL && errno == -1)
		return (print_error("ALLOCATION FAILED\n", -1));
	else if (token == NULL)
		return (-2);
	token = remove_quote(token);
	ret = parser(token, mini);
	if (ret == -1)
		return (ret);
	return (ret);
}
