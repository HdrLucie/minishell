/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:17:48 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/27 17:24:00 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_list_add_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*last;

	if (new == NULL)
		return (-1);
	if (alst == NULL)
	{
		alst = &new;
		return (0);
	}
	last = ft_list_last(*alst);
	last->next = new;
	return (0);
}

void	ft_list_add_front(t_cmd **alst, t_cmd *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_list_clear(t_cmd **lst)
{
	t_cmd	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_list_delone((*lst));
		(*lst) = tmp;
	}
}

int		ft_list_size(t_cmd *lst)
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

t_cmd	*ft_list_last(t_cmd *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		else
			lst = lst->next;
	}
	return (lst);
}

void	ft_list_delone(t_cmd *lst)
{
	if (lst)
		free(lst);
}

t_cmd	*ft_list_new(char **cmd, int built_in, t_redir in, t_redir out)
{
	t_cmd	*tab;

	if (!(tab = malloc(sizeof(t_cmd))))
		return (NULL);
	tab->cmd = cmd;
	tab->built_in = built_in;
	tab->in = in;
	tab->out = out;
	tab->next = NULL;
	return (tab);
}
