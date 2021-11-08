/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:49:24 by hlucie            #+#    #+#             */
/*   Updated: 2021/11/08 10:33:02 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(t_mini *mini, int ret, int flag_exec)
{
	if (mini->cmd)
		ft_cmd_clear(mini->cmd);
	if (mini->env)
		free_env(*mini->env);
	if (mini->exe)
		free_strs(mini->exe);
	if (mini->envp && mini->f_envp)
		free_strs(mini->envp);
	if (mini->red)
		free_red(mini->red, mini->nb_red);
	if (flag_exec == 0)
		return ;
	if (ret < 0)
		exit (ret);
	if (ret == -1 && mini->old_ret)
		exit(mini->old_ret);
	else if (ret != -1)
		exit(ret);
	else
		exit (0);
}

int	check_string(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '-')
			i++;
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free_node(env);
		env = tmp;
	}
	env = NULL;
}

void	ft_exit(t_mini *mini, int flag_exec)
{
	int	ret;
	int	flag_msg;

	ret = -1;
	flag_msg = 0;
	if (mini->nb_pipe == 0 && flag_exec != 0)
		write(2, "exit\n", 5);
	if (mini->exe && mini->exe[1])
		ret = ft_atoi(mini->exe[1]) % 256;
	if (mini->exe && mini->exe[1] && check_string(mini->exe[1]) == 1)
	{
		flag_msg = 1;
		ret = 2;
		write(2, "MINISHELL: exit: numeric argument required\n", 43);
	}
	if (mini->exe && ft_strslen(mini->exe) > 2 && flag_msg == 0)
	{
		write(2, "MINISHELL : exit: too many arguments\n", 37);
		ret = 1;
	}
	free_struct(mini, ret, flag_exec);
}
