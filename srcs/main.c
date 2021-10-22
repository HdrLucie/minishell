/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:57:37 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/22 15:28:24 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *msg, int retur)
{
	write(2, "MINISHELL : ", 12);
	write(2, msg, ft_strlen(msg));
	return (retur);
}

char	**print_char_error(char *msg, int retur)
{
	write(2, "MINISHELL : ", 12);
	write(2, msg, ft_strlen(msg));
	if (retur == -1)
		errno = -1;
	return (NULL);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		// write(1, strs[i], ft_strlen(strs[i]));
		// write(1, "|\n", 2);
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
}

void	init_mini_struct(t_mini *mini, char **envp, t_env **env)
{
	mini->env = env;
	mini->cmd = NULL;
	mini->exe = NULL;
	mini->envp = envp;
	mini->f_envp = 0;
	mini->red = NULL;
	mini->nb_red = 0;
	mini->old_ret = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_mini	mini;
	t_env	*env;

	if (ac != 1)
		return (print_error("TOO MUCH ARG", -1));
	(void)av;
	env = create_env_lst(envp);
	if (env == NULL)
		return (print_error("ALLOCATION FAILED\n", -1));
	init_mini_struct(&mini, envp, &env);
	while (42)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, sig_quit);
		str = readline("> ");
		if (!str)
			return (-1);
		if (ft_strcmp(str, ""))
			add_history(str);
		if (lexer(str, &mini) == -1 || errno == -1)
			return (-1);
		free(str);
	}
	rl_clear_history();
	return (0);
}