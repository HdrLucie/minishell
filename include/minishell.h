/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:09:59 by elisehautef       #+#    #+#             */
/*   Updated: 2021/11/10 12:34:16 by hlucie           ###   ########.fr       */
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

// # define PAGE_SIZE 4096

extern int	g_flag_fork;

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
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env
{
	int				is_valid;
	int				first_alpha_node;
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*next_alpha;
}					t_env;

typedef struct s_mini
{
	t_env	**env;
	t_cmd	*cmd;
	int		nb_pipe;
	int		*pid;
	char	**exe;
	char	**envp;
	int		f_envp;
	t_redir	*red;
	int		nb_red;
	int		old_ret;
	int		*pipefd;
}				t_mini;

/****************************/
/*			MAIN			*/
/****************************/

void	free_strs(char **strs);
int		print_error(char *msg, int retur, int error);
char	**print_char_error(char *msg, int retur, int error);

/****************************/
/*			SIGNAL			*/
/****************************/

void	sig_int(int num);
void	sig_quit_daughter(int num);
void	signal_ret(int status, t_mini *mini);
void	sig_child(int num);

/****************************/
/*			PARSER			*/
/****************************/
/*
**	expand_var_env.c 
*/
char	**expand_var_env(char **token, t_env **env_lst, int old_ret);
int		isnt_var(char *str, int *i);
/*
**	lexer.c 
*/
char	*ft_reverse_split(char **strs);
int		lexer(char *str, t_mini *mini);
/*
**	lst_cmd_utils.c 
*/
int		ft_cmd_add_back(t_cmd **alst, t_cmd *new);
void	ft_cmd_add_front(t_cmd **alst, t_cmd *new);
void	ft_cmd_clear(t_cmd *lst);
t_cmd	*ft_cmd_last(t_cmd *lst);
t_cmd	*ft_cmd_new(char **cmd);
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
char	**remove_comments(char **split);
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
char	**remove_quote(char **token);

/****************************/
/*			CMD				*/
/****************************/
/*
**	init_cmd.c 
*/
int		fill_cmd(char **token, char **envp, t_env **env_lst);
int		ft_execute_cmd(t_mini *mini);
int		execute(char **cmd, t_mini *mini);
/*
**	redir.c 
*/
int		redir(char **exe, t_mini *mini);
int		fill_red(char **cmd, t_redir *red, char **exe);
void	free_red(t_redir *red, int size);
int		count_redir(char **cmd);
void	print_redir(t_redir	*red, int count, char **cmd);
char	**ft_realloc_strs(char **strs, size_t size);
int		parse_redir(char **cmd, int i, t_redir *red, int j);
/*
**	exe_redir.c 
*/
int		exe_redir(t_redir *redir, int count);
int		close_fd(t_redir *red, int count);
int		exe_cmd(t_mini *mini);
/*
**	here_document.c 
*/
int		do_here_doc(t_redir *red);
int		exe_here_doc(t_redir *red, int count);

/****************************/
/*			BUILTINS		*/
/****************************/

t_env	*find_first_alpha_node(t_env *env);
void	ft_print_env_alpha(t_env *env);
void	ft_exit(t_mini *mini, int flag_exec);
void	free_env(t_env *env);
void	udpate_alpha_road(t_env *env);
void	free_node(t_env *node);
t_env	*create_env_lst(char **env);
int		ft_fill_env_lst(char *str, t_env *env);
void	lstadd_back_env(t_env **alst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);
int		ft_fill_env_lst_value(char *str, t_env *env, int i);
int		is_in_env(t_env *env, char *var_export);
int		export_var(t_env *env, char **var_export);
int		create_export_node(t_env *env, int flag, char *name, char *value);
int		fill_env_lst_name(char *str, t_env *env);
int		unset_var(t_env **env, char *unset_var_name);
int		recover_cmd(t_mini *mini);
void	ft_print_env(t_env *env);
int		print_pwd(void);
int		echo(char **to_print);
int		change_directory(t_env *env, char *start, char *cmd);
int		change_exp_value(t_env *env, char *name_exp, char *value_exp);
void	change_directory_home(t_env *env, char **home, char **pwd);
int		change_directory_previous(t_env *env, char **pwd, char **oldpwd);
void	change_directory_root(t_env *env, char **pwd);
char	**env_execve(t_mini *mini);
int		relative_path(t_env *env, char *path, char **pwd);
int		check_last_slash(char *str);
int		check_export_value(char *var_export);
int		search_value(t_env *env, char **value, char *to_find);
int		go_home(t_env *env, int i, char *path, char *pwd);
void	if_free(char *str);
int		check_cd(t_env *env, char *start);
int		check_chdir_ret(char *path);
int		is_in_str(char *str, char c);
t_env	*create_ign_env(t_env *env);
int		set_valid_flag(char *cmd);
int		check_string(char *str);
int		ret_simple_cd(int ret, char *pwd);
void	change_path(t_env *env, char *f_path, char *sec_path, char c);
int		is_oldpwd(t_env *env, char *oldpwd);

/****************************/
/*			PRINT			*/
/****************************/

void	print_env(t_env *env);
void	print_env_alpha(t_env *env);

/****************************/
/*			PIPE			*/
/****************************/

int		exe_pipe(t_mini *mini, t_cmd *cmd, int i);
int		init_pipe(t_mini *mini);
int		init_save_fd(t_mini *mini);
void	close_pipe(int *fd);
void	close_all_pipe(t_mini *mini);
#endif