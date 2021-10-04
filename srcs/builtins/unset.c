/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:31:07 by hlucie            #+#    #+#             */
/*   Updated: 2021/09/30 16:04:09 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes_builtins.h"

t_env   *ft_unset_var(t_env *env, char *unset_var)
{
    t_env   *tmp = NULL;
    t_env   *new_node = env;
    while (env)
    {
        if (ft_strncmp(env->next->name, unset_var, ft_strlen(unset_var)))
            env = env->next;
        else
        {
            // printf("%s\n", env->name);
            tmp = env;
            new_node = env->next->next;
            // printf("FOUND %s | %s\n", tmp->name, new_node->name);
            free(env->name);
            free(env->value);
            free(env);
            tmp = new_node;
            return (tmp);
            // printf("FOUND %s | %s\n", tmp->name, new_node->name);
        }
        env = env->next;
    }
    return (NULL);
}