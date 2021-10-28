/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:02:36 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/28 21:57:06 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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