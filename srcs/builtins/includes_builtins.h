/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes_builtins.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:44:56 by hlucie            #+#    #+#             */
/*   Updated: 2021/09/28 12:42:39 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_BUILTINS_H
# define INCLUDES_BUILTINS_H

# include "../../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct  s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
}               t_env;

int     create_env_lst(char **env);
int     ft_fill_env_lst(char *str, t_env *env);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
t_env   *ft_lstlast_env(t_env *lst);

#endif
