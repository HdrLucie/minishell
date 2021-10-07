/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:10:50 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/07 16:57:44 by ehautefa         ###   ########.fr       */
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

t_cmd	*find_cmd_struct(t_cmd *cmd, char **tmp, t_redir in, t_redir out)
{
	t_cmd	*last;
	t_cmd	*new;

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
			return (NULL);
	}
	else
	{
		new = ft_cmd_new(tmp, in, out);
		if (new == NULL)
			return (NULL);
		ft_cmd_add_back(&cmd, new);
	}
	return (cmd);
}

t_cmd	*parse_pipe(t_cmd *cmd, char **token, int *begin, int i)
{
	char	**tmp;
	t_redir	out;
	t_redir	in;
	t_cmd	*new;

	out.op[0] = '|';
	in.op[0] = '0';
	tmp = ft_substrs(&token[*begin], i - *begin);
	if (tmp == NULL)
		return (NULL);
	cmd = find_cmd_struct(cmd, tmp, in, out);
	if (cmd == NULL)
		return (NULL);
	new = ft_cmd_new(NULL, out, in);
	if (new == NULL)
		return (NULL);
	ft_cmd_add_back(&cmd, new);
	*begin = i + 1;
	return (cmd);
}

t_cmd	*parse_end(t_cmd *cmd, char **token, int *begin, int i)
{
	char	**tmp;
	t_redir	vide;
	t_cmd	*last;

	vide.op[0] = '0';
	tmp = ft_substrs(&token[*begin], i - *begin);
	if (tmp == NULL)
		return (NULL);
	last = ft_cmd_last(cmd);
	cmd = find_cmd_struct(cmd, tmp, vide, vide);
	if (cmd == NULL)
		return (NULL);
	*begin = i + 1;
	return (cmd);
}
