/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:15:45 by ehautefa          #+#    #+#             */
/*   Updated: 2021/08/23 14:51:41 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	long		res;
	int			signe;
	int			tmp;

	i = 0;
	res = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i])
		i++;
	signe = 1;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	tmp = i;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - 48;
	if ((res > LONG_MAX || (i - tmp) > 20) && signe == -1)
		return (0);
	else if ((res > LONG_MAX || (i - tmp) > 20) && signe == 1)
		return (-1);
	if (str[0] == '-' && str[1] == '\0')
		return (2);
	else
		return (res * signe);
}
