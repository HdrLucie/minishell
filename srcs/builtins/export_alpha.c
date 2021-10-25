/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:02:36 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/25 17:16:10 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_node_alpha(t_env **start, t_env **current_node, t_env **next_node, t_env *env)
{
	*start = find_first_alpha_node(env);
	*current_node = find_first_alpha_node(env);
	(*current_node)->first_alpha_node = 0;
	*next_node = NULL;	
}

void	udpate_alpha_road(t_env *env)
{
	int		i;
	t_env	*start;
	t_env	*next_node;
	t_env	*current_node;
	t_env	*tmp;

	i = 0;
	init_node_alpha(&start, &current_node, &next_node, env);
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
