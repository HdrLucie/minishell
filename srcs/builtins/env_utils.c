/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 04:06:57 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/19 12:44:00 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    fill_execve(t_env *env, char **execve)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (env)
	{
		while (env->name[i])
		{
			execve[j][k] = env->name[i];
			i++;
			k++;
		}
		execve[j][k] = '=';
		i = 0;
		k++;
		while (env->value[i])
		{
			execve[j][k] = env->value[i];
			i++;
			k++;
		}
		execve[j][k] = '\0';
		k = 0;
		i = 0;
		j++;
		env = env->next;
	}
}

int malloc_execve(t_env *env, char **execve)
{
	int i;
	int size_name;
	int size_value;
	t_env   *tmp;

	i = 0;
	size_name = 0;
	size_value = 0;
	tmp = env;
	while (env)
	{
		size_name = ft_strlen(env->name);
		size_value = ft_strlen(env->value);
		execve[i] = malloc(sizeof(char) * size_value + size_name + 2);
		i++;
		env = env->next;
	}
	fill_execve(tmp, execve);
	execve[i] = NULL;
	return (1);
}

char	**env_execve(t_mini *mini)
{
	int     nb_var;
	t_env   *tmp;

	if (mini->envp && mini->f_envp)
		free_strs(mini->envp);
	mini->envp = NULL;
	nb_var = 0;
	tmp = *mini->env;
	while (tmp)
	{
		nb_var++;
		tmp = tmp->next;
	}
	mini->envp = malloc(sizeof(char *) * nb_var + 1);
	if (!mini->envp)
		return (NULL);
	mini->f_envp = 1;
	malloc_execve(*mini->env, mini->envp);
	return(mini->envp);
}