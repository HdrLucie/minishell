/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 04:06:57 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/14 05:17:08 by hlucie           ###   ########.fr       */
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
        printf("%s\n", env->name);
        while (env->name[i])
        {
            execve[j][k] = env->name[i];
            i++;
            k++;
        }
        execve[j][k] = '=';
        printf("%s\n", execve[j]);
        i = 0;
        while (env->value[i])
        {
            execve[j][k] = env->value[i];
            i++;
            k++;
        }
        execve[j][k] = '\0';
        k = 0;
        j++;
        env = env->next;
    }
    execve[j] = NULL;
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
    return (1);
}

int env_execve(t_env *env)
{
    char    **execve;
    int     nb_var;
    t_env   *tmp;

    execve = NULL;
    nb_var = 0;
    tmp = env;
    while (env)
    {
        nb_var++;
        env = env->next;
    }
    execve = malloc(sizeof(char *) * nb_var + 1);
    if (!execve)
        return (-1);
    malloc_execve(tmp, execve);
    // int i = 0;
    // while (execve[i])
    // {
    //     printf("%s\n", execve[i]);
    //     i++;
    // }
    return(0);
}