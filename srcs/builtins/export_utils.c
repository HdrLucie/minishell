/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:50:37 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/08 17:43:14 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_first_alpha_node(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env)
	{
		if (env->first_alpha_node == 1)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	udpate_alpha_road(t_env *env)
{
	int		i;
	t_env	*start;
	t_env	*next_node;
	t_env	*current_node;
	t_env	*tmp;

	i = 0;
	start = find_first_alpha_node(env);
	current_node = find_first_alpha_node(env);
	current_node->first_alpha_node = 0;
	next_node = NULL;
	tmp = current_node;
	while (current_node->next_alpha)
	{
		if (ft_strcmp(current_node->name, current_node->next_alpha->name) > 0)
		{
			next_node = current_node->next_alpha;
			current_node->next_alpha = next_node->next_alpha;
			next_node->next_alpha = current_node;
			if (i == 0)
			{
				current_node = next_node;
				start = current_node;
			}
			else
			{
				tmp->next_alpha = next_node;
				current_node = start;
				i = 0;
			}
		}
		else
		{
			tmp = current_node;
			current_node = current_node->next_alpha;
			i++;
		}
	}
	start->first_alpha_node = 1;
	print_env_alpha(start);
}
