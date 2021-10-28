/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:16:29 by ehautefa          #+#    #+#             */
/*   Updated: 2021/10/28 15:21:04 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	ft_count_char(unsigned int num)
{
	int				i;

	i = 0;
	while (num >= 1)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa_unsigned(unsigned int num)
{
	int				i;
	char			*str;
	int				size;

	i = 1;
	size = 1;
	if (num != 0)
		size = ft_count_char(num);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	if (num != 0)
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
