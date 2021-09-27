/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:56:39 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/27 17:50:50 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

typedef struct  s_redir
{
	int     fd;
	char    *chevron;
	char    *file;
}               t_redir; 

typedef struct  s_cmd
{
	char			**cmd;
	int				built_in;
	t_redir			in;
	t_redir			out;
	struct s_cmd	*next;
}               t_cmd;

void	free_strs(char **strs);
int 	print_error(char *msg, int retur);
int 	lexer(char *str, char **envp);
int		ft_list_add_back(t_cmd **alst, t_cmd *new);
void	ft_list_add_front(t_cmd **alst, t_cmd *new);
void	ft_list_clear(t_cmd **lst);
int		ft_list_size(t_cmd *lst);
t_cmd	*ft_list_last(t_cmd *lst);
void	ft_list_delone(t_cmd *lst);
t_cmd	*ft_list_new(char **cmd, int built_in, t_redir in, t_redir out);
int		parse_cmd(char *cmd);

#endif