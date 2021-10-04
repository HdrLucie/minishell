/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:37:41 by user42            #+#    #+#             */
/*   Updated: 2021/10/04 14:37:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes_builtins.h"

int print_pwd(t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->name, "PWD"))
            env = env->next;
        else
        {
            printf("%s\n", env->value);
            return (1);
        }
    }
    return (0);
}