/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:10:50 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/31 13:00:22 by elisehautef      ###   ########.fr       */
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

t_cmd	*find_cmd_struct(t_cmd *cmd, char **tmp)
{
	t_cmd	*last;
	t_cmd	*new;

	last = ft_cmd_last(cmd);
	if (cmd && last->cmd == NULL)
	{
		last->cmd = tmp;
	}
	else if (!cmd)
	{
		cmd = ft_cmd_new(tmp);
		if (cmd == NULL)
			return (NULL);
	}
	else
	{
		new = ft_cmd_new(tmp);
		if (new == NULL)
			return (NULL);
		ft_cmd_add_back(&cmd, new);
	}
	return (cmd);
}

t_cmd	*parse_pipe(t_cmd *cmd, char **token, int *begin, int i)
{
	char	**tmp;
	t_cmd	*new;

	tmp = ft_substrs(&token[*begin], i - *begin);
	if (tmp == NULL)
		return (NULL);
	cmd = find_cmd_struct(cmd, tmp);
	if (cmd == NULL)
		return (NULL);
	new = ft_cmd_new(NULL);
	if (new == NULL)
		return (NULL);
	ft_cmd_add_back(&cmd, new);
	*begin = i + 1;
	return (cmd);
}

t_cmd	*parse_end(t_cmd *cmd, char **token, int *begin, int i)
{
	char	**tmp;
	t_cmd	*last;

	tmp = ft_substrs(&token[*begin], i - *begin);
	if (tmp == NULL)
		return (NULL);
	last = ft_cmd_last(cmd);
	cmd = find_cmd_struct(cmd, tmp);
	if (cmd == NULL)
		return (NULL);
	*begin = i + 1;
	return (cmd);
}
