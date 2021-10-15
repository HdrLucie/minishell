/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:21:45 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/14 03:38:23 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_find_substitute(char *to_print, int last_char, char **to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (to_print[i] == '$' && to_print[i + 1] == '{'
		&& to_print[last_char] == '}')
	{
		i = 2;
		*to_find = malloc(sizeof(char) * (last_char - 1));
		if (!(*to_find))
			return (-1);
		while (to_print[i] && to_print[i] != '}')
			(*to_find)[j++] = to_print[i++];
	}
	(*to_find)[j] = '\0';
	return (1);
}

int	print_substitute(t_env *env, char *to_print)
{
	int		j;
	int		last_char;
	char	*to_find;

	j = 0;
	last_char = ft_strlen(to_print) - 1;
	to_find = NULL;
	if (!to_find_substitute(to_print, last_char, &to_find))
		return (-1);
	if (to_print[j] == '$' && to_print[j + 1] == '{')
	{
		if (to_print[last_char] != '}')
			return (-1);
		else
		{
			while (env)
			{
				if (!ft_strncmp(env->name, to_find, ft_strlen(to_find)))
				{
					printf("%s\n", env->value);
					free(to_find);
					return (0);
				}
				env = env->next;
			}
		}
	}
	free(to_find);
	return (1);
}

int	echo(char **to_print, t_env *env)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!to_print[1])
		return (-2);
	if (!print_substitute(env, to_print[1]))
		return (0);
	while (to_print[i])
	{
		while (to_print[i][j])
		{
			if (to_print[i][j] == '-' && to_print[i][j + 1] == 'n')
				j += 2;
			printf("%c", to_print[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	printf("\n");
	return (0);
}
