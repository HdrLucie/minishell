/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:26:03 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/05 10:03:22 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_free_node(t_env *node)
{
	if (node->name)
		free(node->name);
	if (node->value)
    free(node->value);
	if (node)
    	free(node);
}

void	ft_free_lst(t_env **list)
{
	t_env	*tmp;

	tmp = *list;
	if (list)
	{
		while (*list)
		{
			tmp = *list;
			(*list) = (*list)->next;
			free(tmp);
		}
	}
	*list = NULL;
}

int	ft_create_export_node(t_env *env, char *name, char *value)
{
	t_env	*current_node;

	current_node = NULL;
	current_node = malloc(sizeof(t_env));
	current_node->name = name;
	current_node->value = value;
	ft_lstadd_back_env(&env, current_node);
	return (1);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = ft_lstlast_env(*alst);
	if (tmp == NULL)
		*alst = new;
	else
		tmp->next = new;
	new->next = NULL;
}
