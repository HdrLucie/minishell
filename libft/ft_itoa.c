/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:16:29 by ehautefa          #+#    #+#             */
/*   Updated: 2021/08/23 14:50:44 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	ft_count_char(int n)
{
	int				i;
	unsigned int	num;

	i = 1;
	num = -n;
	if (n == 0)
		return (1);
	if (n >= 0)
	{
		i = 0;
		num = n;
	}
	while (num >= 1)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*str;
	int				size;
	unsigned int	num;

	i = 1;
	size = ft_count_char(n);
	num = -n;
	if (n >= 0)
		num = n;
	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	if (n != 0)
		str[0] = '-';
	while (num >= 1)
	{
		str[size - i] = num % 10 + '0';
		num = num / 10;
		i++;
	}
	str[size] = '\0';
	return (str);
}
