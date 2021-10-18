/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:29:30 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/18 15:16:12 by elise            ###   ########.fr       */
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
		if (!ft_strcmp(token[i], ";"))
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
	ft_cmd_clear(cmd);
	return (0);
}

int	expand(char **token, int i, t_env env)
{
	token[i] = ft_realloc(token[i], ft_strlen(env.value));
	if (token[i] == NULL)
		return (print_error("ALLOCATION FAILED\n", -1));
	ft_strcpy(token[i], env.value);
	return (0);
}

char **expand_var_env(char **token, t_env **env_lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (token && token[i])
	{
		if (token[i][0] == '$')
		{
			tmp = *env_lst;
			while (tmp)
			{
				if (ft_strcmp(&token[i][1], tmp->name) == 0)
				{
					if (expand(token, i, *tmp) == -1)
						return (NULL);
					tmp = NULL;
				}
				else
					tmp = tmp->next;
			}
			if (token[i][0] == '$')
				token[i][0] = '\0';
		}
		i++;
	}
	return (token);
}

int	lexer(char *str, char **envp, t_env **env_lst)
{
	char	**token;
	int		ret;

	token = ft_split_dollar(str);
	if (token == NULL)
		return (-1);
	token = expand_var_env(token, env_lst);
	if (token == NULL)
		return (-1);
	token = ft_split_quote(ft_reverse_split(token, ' '));
	if (token == NULL && errno == -1)
		return (print_error("ALLOCATION FAILED\n", -1));
	else if (token == NULL)
		return (-2);
	ret = parser(token, envp, env_lst);
	if (ret == -1)
		return (ret);
	return (ret);
}
