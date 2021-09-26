/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:56:39 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/26 18:56:07 by ehautefa         ###   ########.fr       */
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


int print_error(char *msg, int retur);
int ft_main_parse(char *str, char **envp);
#endif