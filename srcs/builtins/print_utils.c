/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 03:16:39 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/29 14:06:33 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	int	last_char;

	last_char = 0;
	while (env)
	{
		printf("env->name : %s\n", env->name);
		last_char = ft_strlen(env->name);
		if (env->name && env->name[last_char - 1] == '=')
			printf("%s", env->name);
		if (env->value)
			printf("%s", env->value);
		else
			printf("''");
		printf("\n");
		env = env->next;
	}
}

void	print_env_alpha(t_env *env)
{
	while (env)
	{
		if (env->name)
			printf("declare -x %s", env->name);
		if (env->value)
			printf("\"%s\"", env->value);
		else
			printf("''");
		printf("\n");
		env = env->next_alpha;
	}
}
