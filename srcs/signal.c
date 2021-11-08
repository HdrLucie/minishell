/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:23:31 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/08 11:08:13 by ehautefa         ###   ########.fr       */
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
}

void	sig_quit_daughter(int num)
{
	(void)num;
	if (g_flag_fork == 1)
	{
		write(1, "Quit (core dumped)\n", 19);
	}
	else
	{
		write(1, "\b", 1);
		write(0, "\b", 1);
	}
}
