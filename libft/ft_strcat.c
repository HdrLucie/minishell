/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:17:57 by ehautefa          #+#    #+#             */
/*   Updated: 2021/08/23 14:34:29 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	size_s1;
	int	i;

	i = 0;
	size_s1 = ft_strlen(s1);
	while (s2[i])
	{
		s1[i + size_s1] = s2[i];
		i++;
	}
	s1[i + size_s1] = '\0';
	return (s1);
}
