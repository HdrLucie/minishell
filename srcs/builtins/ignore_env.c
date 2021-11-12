/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:24:36 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/12 10:55:25 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_ign_value(t_env *env)
{
	char	*tmp;
	char	*shlvl;

	tmp = malloc(sizeof(char) * 1000);
	shlvl = malloc(sizeof(char) * 1000);
	if (!tmp || !shlvl)
		return (-1);
	shlvl[0] = '0';
	shlvl[1] = '\0';
	env->name = ft_strdup("LS_COLORS");
	env->value = ft_strdup("");
	env->next->name = ft_strdup("PWD");
	env->next->value = ft_strdup(getcwd(tmp, 1000));
	env->next->next->name = ft_strdup("_");
	env->next->next->value = ft_strdup(ft_strjoin(tmp, "/./minishell"));
	env->next->next->next->name = ft_strdup("SHLVL");
	env->next->next->next->value = ft_itoa(ft_atoi(shlvl) + 1);
	if (!env->name || !env->value || !env->next->name || !env->next->value
		|| !env->next->next->name || !env->next->next->value
		|| !env->next->next->next->name || !env->next->next->next->value)
		return (-1);
	return (0);
}

t_env	*create_ign_env(t_env *env)
{
	t_env	*current_node;
	int		i;

	current_node = NULL;
	i = 0;
	while (i < 4)
	{
		current_node = malloc(sizeof(t_env));
		if (!current_node)
			return (NULL);
		current_node->next = NULL;
		current_node->next_alpha = NULL;
		current_node->is_valid = 1;
		lstadd_back_env(&env, current_node);
		i++;
	}
	fill_ign_value(env);
	return (env);
}
