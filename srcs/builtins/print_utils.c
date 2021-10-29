/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 03:16:39 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/29 14:57:30 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	int	last_char;

	last_char = 0;
	while (env)
	{
		last_char = ft_strlen(env->name);
		if (env->name && env->name[last_char - 1] == '=')
		{
			printf("%s", env->name);
			if (env->value[0] == '\0')
				printf("\n");
		}
		if (env->value[0] != '\0')
			printf("%s\n", env->value);
		// else
		// 	printf("''");
		env = env->next;
	}
}

void	print_env_alpha(t_env *env)
{
	int	last_char;

	last_char = 0;
	while (env)
	{
		last_char = ft_strlen(env->name);
		if (env->name)
			printf("declare -x %s", env->name);
		if (env->value)
		{
			if (env->name[last_char - 1] != '=')
				printf("=");
			printf("\"%s\"", env->value);
		}
		// else
		// 	printf("''");
		printf("\n");
		env = env->next_alpha;
	}
}
