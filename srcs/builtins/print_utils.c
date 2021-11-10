/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 03:16:39 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/10 14:40:43 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	print_env(t_env *env)
{
	int	last_char;

	last_char = 0;
	if (is_in_env(env, "PATH") == 0)
		return (127);
	while (env)
	{
		last_char = ft_strlen(env->name);
		if (env->name && env->is_valid == 1)
		{
			write(1, env->name, ft_strlen(env->name));
			write(1, "=", 1);
			if (env->value[0] == '\0')
				write(1, "\n", 1);
		}
		if (env->value[0] != '\0')
		{
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}

void	print_env_alpha(t_env *env)
{
	int	last_char;

	last_char = 0;
	while (env)
	{
		last_char = ft_strlen(env->name);
		if (env->name)
		{
			write(1, "declare -x ", 11);
			write(1, env->name, ft_strlen(env->name));
		}
		if (env->value && env->is_valid)
		{
			printf("=\"%s\"", env->value);
		}
		printf("\n");
		env = env->next_alpha;
	}
}
