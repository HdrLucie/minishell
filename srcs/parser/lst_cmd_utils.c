/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:17:48 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/06 12:31:29 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_add_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*last;

	last = *alst;
	if (new == NULL)
		return (-1);
	if (alst == NULL)
	{
		alst = &new;
		return (0);
	}
	while (last->next)
		last = last->next;
	last->next = new;
	return (0);
}

void	ft_cmd_add_front(t_cmd **alst, t_cmd *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_cmd_clear(t_cmd **lst)
{
	t_cmd	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_cmd_delone((*lst));
		(*lst) = tmp;
	}
}

int	ft_cmd_size(t_cmd *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

t_cmd	*ft_cmd_last(t_cmd *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_cmd_delone(t_cmd *lst)
{
	if (lst)
		free(lst);
}

t_cmd	*ft_cmd_new(char **cmd, t_redir in, t_redir out)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->in = in;
	new->out = out;
	new->next = NULL;
	return (new);
}
