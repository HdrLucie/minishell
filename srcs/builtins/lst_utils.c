/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:26:03 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/08 15:43:49 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_node(t_env *node)
{
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	if (node)
		free(node);
}

int	create_export_node(t_env *env, char *name, char *value)
{
	t_env	*current_node;

	current_node = NULL;
	current_node = malloc(sizeof(t_env));
	current_node->name = name;
	current_node->value = value;
	current_node->first_alpha_node = 0;
	lstadd_back_env(&env, current_node);
	return (1);
}

t_env	*lstlast_env(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_env	*lstlast_env_alpha(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next_alpha != NULL)
		lst = lst->next_alpha;
	return (lst);
}

void	lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = NULL;
	tmp2 = lstlast_env_alpha(find_first_alpha_node(*alst));
	tmp = lstlast_env(*alst);
	if (tmp == NULL)
	{
		new->first_alpha_node = 1;
		*alst = new;
		return ;
	}
	else
	{
		new->first_alpha_node = 0;
		tmp->next = new;
		tmp2->next_alpha = new;
	}
	new->next = NULL;
	new->next_alpha = NULL;
}
