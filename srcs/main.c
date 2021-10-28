/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:57:37 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 18:54:50 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*find_couleur(void)
{
	static int	i = 0;

	i++;
	if (i > 5)
		i = 0;
	if (i == 0)
		return("\033[1m\033[31m");
	if (i == 1)
		return("\033[1m\033[32m");
	if (i == 2)
		return("\033[1m\033[33m");
	if (i == 3)
		return("\033[1m\033[34m");
	if (i == 4)
		return("\033[1m\033[35m");
	if (i == 5)
		return("\033[1m\033[36m");
	return("\033[1m\033[36m");
}

char	*init_prompt(void)
{
	char	*prompt;
	int		i;

	i = 0;
	prompt = malloc(1000 * sizeof(char));
	if (prompt == NULL)
		return (*print_char_error("ALLOCATION FAILED\n", -1));
	ft_strcpy(prompt, find_couleur());
	while (prompt[i])
		i++;
	getcwd(&prompt[i], 950);
	if (prompt == NULL)
		return (*print_char_error("TOO MUCH CHAR ON PWD\n", -1));
	while (prompt[i])
		i++;
	ft_strcpy(&prompt[i], "\033[0m$ ");
	return (prompt);
}

int	launch_minishell(t_mini *mini)
{
	char	*str;
	char	*prompt;

	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	prompt = init_prompt();
	if (prompt == NULL)
		return (-1);
	str = readline(prompt);
	free(prompt);
	if (str[0] == '\0')
		return (0);
	if (ft_strcmp(str, ""))
		add_history(str);
	if (lexer(str, mini) == -1 || errno == -1)
		return (-1);
	free(str);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;
	t_env	*env;

	if (ac != 1)
		return (print_error("TOO MUCH ARG", -1));
	(void)av;
	g_flag_fork = 0;
	env = create_env_lst(envp);
	if (env == NULL)
		return (print_error("ALLOCATION FAILED\n", -1));
	init_mini_struct(&mini, envp, &env);
	while (42)
	{
		if (launch_minishell(&mini) == -1)
			return (-1);
	}
	rl_clear_history();
	return (0);
}
