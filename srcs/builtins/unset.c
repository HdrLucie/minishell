/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:31:07 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/08 15:43:49 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_alpha_var(t_env *env, char *unset_alpha_var_name)
{
	t_env	*tmp_alpha;
	t_env	*current_alpha_node;

	tmp_alpha = NULL;
	current_alpha_node = find_first_alpha_node(env);
	if (!ft_strcmp(current_alpha_node->name, unset_alpha_var_name))
	{
		current_alpha_node->next_alpha->first_alpha_node = 1;
		return (1);
	}
	while (current_alpha_node->next)
	{
		if (!ft_strcmp(current_alpha_node->next_alpha->name,
				unset_alpha_var_name))
		{
			tmp_alpha = current_alpha_node->next_alpha->next_alpha;
			current_alpha_node->next_alpha = tmp_alpha;
			return (1);
		}
		current_alpha_node = current_alpha_node->next_alpha;
	}
	return (0);
}

int	unset_var(t_env **env, char *unset_var_name)
{
	t_env	*tmp;
	t_env	*current_node;

	tmp = NULL;
	current_node = *env;
	if (!unset_alpha_var(*env, unset_var_name))
		return (0);
	if (!ft_strcmp((*env)->name, unset_var_name))
	{
		tmp = *env;
		*env = (*env)->next;
		free_node(tmp);
		return (1);
	}
	while (current_node->next)
	{
		if (!ft_strcmp(current_node->next->name, unset_var_name))
		{
			tmp = current_node->next->next;
			free_node(current_node->next);
			current_node->next = tmp;
			return (1);
		}
		current_node = current_node->next;
	}
	return (0);
}
