/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:37:41 by user42            #+#    #+#             */
/*   Updated: 2021/10/05 10:03:22 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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