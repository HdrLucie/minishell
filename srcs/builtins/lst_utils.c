/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:26:03 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/06 16:14:51 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_first_alpha_node(t_env *env)
{
	if(env == NULL)
		return (NULL);
	while (env)
	{
		if (env->first_alpha_node == 1)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_udpate_alpha_road(t_env *env)
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
	ft_print_env_alpha(start);
}

void 	ft_free_node(t_env *node)
{
	if (node->name)
		free(node->name);
	if (node->value)
    free(node->value);
	if (node)
    	free(node);
}

int	ft_create_export_node(t_env *env, char *name, char *value)
{
	t_env	*current_node;

	current_node = NULL;
	current_node = malloc(sizeof(t_env));
	current_node->name = name;
	current_node->value = value;
	current_node->first_alpha_node = 0;
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

t_env	*ft_lstlast_env_alpha(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next_alpha != NULL)
		lst = lst->next_alpha;
	return (lst);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;
	t_env 	*tmp2;

	tmp = NULL;
	tmp2 = ft_lstlast_env_alpha(find_first_alpha_node(*alst));
	tmp = ft_lstlast_env(*alst);
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
