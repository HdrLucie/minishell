/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:09:59 by elisehautef       #+#    #+#             */
/*   Updated: 2021/10/19 11:46:41 by elise            ###   ########.fr       */
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

/****************************/
/*			DEFINE			*/
/****************************/

# define PAGE_SIZE 4096

/****************************/
/*			STRUCT			*/
/****************************/

typedef struct s_redir
{
	int		n;
	char	op[3];
	char	*path;
	int		save_fd;
}				t_redir;

typedef struct s_cmd
{
	char			**cmd;
	int				pipe_in;
	int				pipe_out;
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
char	**print_char_error(char *msg, int retur);

/****************************/
/*			SIGNAL			*/
/****************************/

void	sig_int(int num);
void	sig_quit(int num);

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
t_cmd	*ft_cmd_new(char **cmd, int in, int out);
/*
** 	split_quote.c
*/
char	**ft_split_quote(char *str);
int		check_quote(char *str, int i);
int		is_space(char c);
int		is_redir(char c);
int		is_spe_char(char c);
int		find_token(char *str, int i, char end);
char	**ft_split_dollar(char *str);
/*
**	parse_path.c 
*/
char	*parse_cmd(char *cmd, char **envp);
/*
**	parser.c 
*/
t_cmd	*parse_pipe(t_cmd *cmd, char **token, int *begin, int i);
t_cmd	*parse_end(t_cmd *cmd, char **token, int *begin, int i);
char	**ft_substrs(char **s, size_t len);

/****************************/
/*			CMD				*/
/****************************/
/*
**	init_cmd.c 
*/
int		fill_cmd(char **token, char **envp, t_env **env_lst);
int		ft_execute_cmd(t_cmd *cmd, char **envp, t_env **env_lst);
int		execute(char **cmd, char **envp);
/*
**	redir.c 
*/
int		redir(char **cmd, t_cmd *lst, char **envp, t_env **env_lst);
void	free_red(t_redir *red, int size);
int		count_redir(char **cmd);
void	print_redir(t_redir	*red, int count, char **cmd);
char	**ft_realloc_strs(char **strs, size_t size);
/*
**	exe_redir.c 
*/
int		exe_redir(t_redir *redir, int count);
int		close_fd(t_redir *red, int count);
int		exe_cmd(char **exe, t_cmd *lst, char **envp, t_env **env_lst);
/****************************/
/*			BUILTINS		*/
/****************************/

t_env	*find_first_alpha_node(t_env *env);
void	ft_print_env_alpha(t_env *env);
void	ft_exit(t_env *env, t_cmd *cmd, char **exe);
void	udpate_alpha_road(t_env *env);
void	free_node(t_env *node);
t_env	*create_env_lst(char **env);
int		ft_fill_env_lst(char *str, t_env *env);
void	lstadd_back_env(t_env **alst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);
int		ft_fill_env_lst_value(char *str, t_env *env, int i);
int		ft_check_env(t_env *env, char *var_export);
int		export_var(t_env *env, char **var_export);
int		create_export_node(t_env *env, char *name, char *value);
int		ft_fill_env_lst_name(char *str, t_env *env);
int		unset_var(t_env **env, char *unset_var_name);
int		recover_cmd(char **cmd, t_env **env, t_cmd *lst);
void	ft_print_env(t_env *env);
int		print_pwd(t_env *env);
int		echo(char **to_print, t_env *env);
int		change_directory(t_env *env, char **cmd);
int		change_exp_value(t_env *env, char *name_exp, char *value_exp);
char	**env_execve(t_env *env, char **execve);

/****************************/
/*			PRINT			*/
/****************************/

void	print_env(t_env *env);
void	print_env_alpha(t_env *env);

#endif