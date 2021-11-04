/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:57:37 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/04 09:17:56 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	g_flag_fork;

int	g_flag_fork;

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
	static int	i = -1;

	i++;
	if (i > 6)
		i = 0;
	if (i == 0)
		return ("\033[1m\033[37m");
	if (i == 1)
		return ("\033[1m\033[31m");
	if (i == 2)
		return ("\033[1m\033[33m");
	if (i == 3)
		return ("\033[1m\033[32m");
	if (i == 4)
		return ("\033[1m\033[34m");
	if (i == 5)
		return ("\033[1m\033[35m");
	if (i == 6)
		return ("\033[1m\033[37m");
	return ("\033[1m\033[37m");
}

char	*init_prompt(void)
{
	char	*prompt;
	int		i;

	i = 0;
	prompt = malloc(1000 * sizeof(char));
	if (prompt == NULL)
		return (*print_char_error("ALLOCATION FAILED\n", -1, errno));
	ft_strcpy(prompt, find_couleur());
	while (prompt[i])
		i++;
	getcwd(&prompt[i], 950);
	if (prompt == NULL)
		return (*print_char_error("TOO MUCH CHAR ON PWD\n", -1, errno));
	while (prompt[i])
		i++;
	ft_strcpy(&prompt[i], "\033[0m$ ");
	return (prompt);
}

int	launch_minishell(t_mini *mini)
{
	char	*str;
	char	*prompt;
	int		ret;

	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
	prompt = init_prompt();
	if (prompt == NULL)
		return (-1);
	str = readline(prompt);
	if (!str)
		return (print_error("exit\n", -1, -1));
	free(prompt);
	if (str[0] == '\0')
		return (0);
	if (ft_strcmp(str, ""))
		add_history(str);
	ret = lexer(str, mini);
	if (ret == -1 || errno == -1)
		return (-1);
	else if (ret == -2)
		mini->old_ret = errno;
	free(str);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;
	t_env	*env;

	if (ac != 1)
		return (print_error("TOO MUCH ARG", -1, errno));
	(void)av;
	g_flag_fork = 0;
	env = create_env_lst(envp);
	if (env == NULL)
		return (print_error("ALLOCATION FAILED\n", -1, errno));
	init_mini_struct(&mini, envp, &env);
	while (42)
	{
		if (launch_minishell(&mini) == -1)
			return (-1);
	}
	rl_clear_history();
	return (0);
}
