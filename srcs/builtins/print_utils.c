/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 03:16:39 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/18 10:56:14 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	// printf("EXECVE\n");
	// env_execve(env);
	// printf("\nEXECVE\n");
	while (env)
	{
		if (env->name)
			printf("%s=", env->name);
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
			printf("declare -x %s=", env->name);
		if (env->value)
			printf("\"%s\"", env->value);
		else
			printf("''");
		printf("\n");
		env = env->next_alpha;
	}
}
