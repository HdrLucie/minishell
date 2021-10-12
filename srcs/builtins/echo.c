/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:21:45 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/12 19:59:12 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **to_print)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	printf("%c | %c | %c\n", to_print[i][0], to_print[i][1], to_print[i][2]);
	while (to_print[i])
	{
		while (to_print[i][j])
		{
			if (to_print[i][j] == '-' && to_print[i][j + 1] == 'n' && to_print[i][j + 3] == ' ')
			{
				printf("HEY\n");
				j += 2;
			}
			printf("%c", to_print[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	printf("\n");
}