/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:26:03 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/30 18:28:01 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_env *node)
{
	if (node->name)
		free(node->name);
	node->name = NULL;
	if (node->value)
		free(node->value);
	node->value = NULL;
	if (node)
		free(node);
	node = NULL;
}

int	create_export_node(t_env *env, char *name, char *value)
{
	t_env	*current_node;

	current_node = NULL;
	current_node = malloc(sizeof(t_env));
	if (!current_node)
		return (print_error("ALLOCATION FAILED\n", -1));
	current_node->name = name;
	current_node->value = value;
	current_node->first_alpha_node = 0;
	current_node->flag_export = 0;
	lstadd_back_env(&env, current_node);
	return (1);
}

t_env	*lstlast_env(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*lstlast_env_alpha(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst && lst->next_alpha)
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
		*alst = new;
		new->first_alpha_node = 1;
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
