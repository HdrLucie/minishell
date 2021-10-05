/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:44:56 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/05 10:02:45 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// # include "../../libft/libft.h"
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

void 	ft_free_node(t_env *node);
t_env	*create_env_lst(char **env);
int		ft_fill_env_lst(char *str, t_env *env);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);
int		ft_fill_env_lst_value(char *str, t_env *env, int i);
int		ft_check_env(t_env *env, char *var_export);
int		ft_export_var(t_env *env, char *var_export);
int		ft_create_export_node(t_env *env, char *name, char *value);
int		ft_fill_env_lst_name(char *str, t_env *env);
int		ft_unset_var(t_env **env, char *unset_var_name);
int		ft_recover_cmd(char **cmd, t_env *env);
void	ft_print_env(t_env *env);
int		print_pwd(t_env *env);

#endif
