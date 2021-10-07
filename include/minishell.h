/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:56:39 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/07 16:58:27 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_redir
{
	int		n;
	char	op[3];
	char	*path;
}				t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_redir			in;
	t_redir			out;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env
{
	int				first_alpha_node;
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*next_alpha;
}					t_env;

/****************************/
/*			MAIN			*/
/****************************/

void	free_strs(char **strs);
int		print_error(char *msg, int retur);
char	*print_char_error(char *msg, int retur);

/****************************/
/*			PARSER			*/
/****************************/

/*
**	lexer.c 
*/
int		lexer(char *str, char **envp, t_env **env_lst);
/*
**	lst_cmd_utils.c 
*/
int		ft_cmd_add_back(t_cmd **alst, t_cmd *new);
void	ft_cmd_add_front(t_cmd **alst, t_cmd *new);
void	ft_cmd_clear(t_cmd *lst);
t_cmd	*ft_cmd_last(t_cmd *lst);
t_cmd	*ft_cmd_new(char **cmd, t_redir in, t_redir out);
/*
** 	split_quote.c
*/
char	**ft_split_quote(char *str);
int		check_quote(char *str, int i);
int		is_space(char *str, int i);
int		is_redir(char *str, int i);
int		is_spe_char(char *str, int i);
int		find_token(char *str, int *i, char end);
/*
**	parse_path.c 
*/
char	*parse_cmd(char *cmd);
/*
**	parser.c 
*/
t_cmd	*parse_pipe(t_cmd *cmd, char **token, int *begin, int i);
t_cmd	*parse_end(t_cmd *cmd, char **token, int *begin, int i);
char	**ft_substrs(char **s, size_t len);

/****************************/
/*			CMD				*/
/****************************/
int		fill_cmd(char **token, char **envp, t_env **env_lst);
int		ft_execute_cmd(t_cmd *cmd, char **envp, t_env **env_lst);

/****************************/
/*			BUILTINS		*/
/****************************/

t_env	*find_first_alpha_node(t_env *env);
void	ft_print_env_alpha(t_env *env);
void    ft_exit(t_env *env, t_cmd *cmd);
void	udpate_alpha_road(t_env *env);
void 	free_node(t_env *node);
t_env	*create_env_lst(char **env);
int		ft_fill_env_lst(char *str, t_env *env);
void	lstadd_back_env(t_env **alst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);
int		ft_fill_env_lst_value(char *str, t_env *env, int i);
int		ft_check_env(t_env *env, char *var_export);
int		export_var(t_env *env, char *var_export);
int		create_export_node(t_env *env, char *name, char *value);
int		ft_fill_env_lst_name(char *str, t_env *env);
int		unset_var(t_env **env, char *unset_var_name);
int		recover_cmd(char **cmd, t_env **env, t_cmd *lst);
void	ft_print_env(t_env *env);
int		print_pwd(t_env *env);

/****************************/
/*			PRINT			*/
/****************************/

void	print_env(t_env *env);
void	print_env_alpha(t_env *env);

#endif