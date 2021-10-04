/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:56:39 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/04 09:39:26 by ehautefa         ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/wait.h>

typedef struct  s_redir
{
	int     n;
	char    *op;
	char    *word;
}               t_redir; 

typedef struct  s_cmd
{
	char			**cmd;
	int				built_in;
	t_redir			*in;
	t_redir			*out;
	struct s_cmd	*next;
}               t_cmd;

void	free_strs(char **strs);
int 	print_error(char *msg, int retur);
int 	lexer(char *str, char **envp);
int		ft_cmd_add_back(t_cmd **alst, t_cmd *new);
void	ft_cmd_add_front(t_cmd **alst, t_cmd *new);
void	ft_cmd_clear(t_cmd **lst);
int		ft_cmd_size(t_cmd *lst);
t_cmd	*ft_cmd_last(t_cmd *lst);
void	ft_cmd_delone(t_cmd *lst);
t_cmd	*ft_cmd_new(char **cmd, int built_in, t_redir *in, t_redir *out);
char	*parse_cmd(char *cmd);
char	**ft_split_quote(char *str);
int		fill_cmd(char **token, char **envp);

#endif