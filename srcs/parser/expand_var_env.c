/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:54:47 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/22 18:03:49 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand(char **token, int i, char *value)
{
	if (value == NULL)
		return (print_error("ALLOCATION FAILED\n", -1));
	token[i] = ft_realloc(token[i], ft_strlen(value) + 1);
	if (token[i] == NULL)
		return (print_error("ALLOCATION FAILED\n", -1));
	ft_strcpy(token[i], value);
	return (0);
}

char	**find_value(t_env *env, char **token, int i)
{
	while (env)
	{
		if ((token[i][1] && token[i][1] == '{'
			&& ft_strcmp(&token[i][2], env->name) == 0)
			|| ft_strcmp(&token[i][1], env->name) == 0)
		{
			if (expand(token, i, env->value) == -1)
				return (NULL);
			env = NULL;
		}
		else
			env = env->next;
	}
	return (token);
}

char	**expand_var_env(char **token, t_env **env_lst, int old_ret)
{
	int		i;

	i = 0;
	while (token && token[i])
	{
		if (token[i][0] == '$' && token[i][1] && token[i][1] == '{')
			token[i][ft_strlen(token[i]) - 1] = '\0';
		if (token[i][0] == '$')
		{
			token = find_value(*env_lst, token, i);
			if (token == NULL)
				return (NULL);
			if (token[i][0] == '$' && token[i][1] == '?'
				&& expand(token, i, ft_itoa(old_ret)) == -1)
				return (NULL);
			else if (token[i][0] == '$')
			{
				if (token[i][1] && ft_isalnum(token[i][1]))
					token[i][0] = '\0';
			}
		}
		i++;
	}
	return (token);
}
