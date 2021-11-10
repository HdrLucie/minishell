/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:43:05 by ehautefa          #+#    #+#             */
/*   Updated: 2021/11/10 15:52:36 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_redir_pipe(t_mini *mini, char *file, int last)
{
	int	ret;
	
	if (file && do_here_doc(mini->red, file, last) == -1)
		return (-1);
	ret = exe_redir(mini->red, mini->nb_red, 1);
	if (ret < 0)
		return (ret);
	ret = exe_cmd(mini);
	close_fd(mini->red, mini->nb_red);
	free_strs(mini->exe);
	free_red(mini->red, mini->nb_red);
	return (ret);
}

char	*redir_pipe(char **exe, t_mini *mini, int *last)
{
	int		ret;
	char	*file;

	ret = 0;
	mini->nb_red = count_redir(exe);
	mini->red = malloc(mini->nb_red * sizeof(t_redir));
	if (mini->red == NULL)
		return (NULL);
	mini->exe = malloc(sizeof(char *) * (ft_strslen(exe) + 1));
	if (mini->exe == NULL)
		return (NULL);
	ret = fill_red(exe, mini->red, mini->exe);
	mini->exe = remove_quote(mini->exe);
	if (ret < 0)
	{
		mini->old_ret = ret;
		return (NULL);
	}
	file = find_file_here_doc(mini->red, mini->nb_red, last);
	if (file == NULL && errno == -1)
		return (NULL);
	return (file);
}