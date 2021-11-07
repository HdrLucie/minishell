/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:54:47 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/07 20:45:01 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_pipe(char *src, char *dest, int begin)
{
	int		i;
	int		j;

	i = begin + 1;
	j = begin;
	dest[j] = '"';
	dest[++j] = '|';
	dest[++j] = '"';
	printf("dest : %s\n", dest);
	while (src && dest && src[i])
	{
		dest[++j] = src[i];
		i++;
	}
	dest[++j] = '\0';
	return (dest);
}

char	*quote_pipe(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			tmp = ft_strdup(str);
			str = ft_realloc(str, ft_strlen(str) + 2);
			if (str == NULL || tmp == NULL)
				return (NULL);
			str = ft_strcpy(str, tmp);
			str = copy_pipe(tmp, str, i);
			printf("str : %s\n", str);
			free(tmp);
			i += 2;
		}
		i++;
	}
	return (str);
}

int	expand(char **token, int i, char *value)
{
	int	size;

	if (value == NULL)
		return (print_error("ALLOCATION FAILED\n", -1, -1));
	size = ft_strlen(value);
	token[i] = ft_realloc(token[i], size + 1);
	if (token[i] == NULL)
		return (print_error("ALLOCATION FAILED\n", -1, -1));
	ft_strcpy(token[i], value);
	token[i] = quote_pipe(token[i]);
	if (token[i] == NULL)
		return (-1);
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
