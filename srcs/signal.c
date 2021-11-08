/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:23:31 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/08 12:18:59 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int num)
{
	(void)num;
	write(1, "\n", 1);
	if (g_flag_fork == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_flag_fork = 0;
}

void	sig_quit_daughter(int num)
{
	signal(num, SIG_IGN);
}

void	signal_ret(int status, t_mini *mini)
{
	if (WIFSIGNALED(status) && g_flag_fork == 1)
		write(1, "Quit (core dumped)\n", 19);
	if (WIFEXITED(status))
		mini->old_ret = WEXITSTATUS(status);
}
