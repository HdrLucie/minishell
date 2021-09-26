/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:26:10 by user42            #+#    #+#             */
/*   Updated: 2021/03/24 08:26:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin_size(char const *s1, char const *s2, int size_s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	str = ft_strnew(ft_strlen(s1) + size_s2);
	if (str == NULL)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j] && j < size_s2)
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free((char *)s1);
	return (str);
}
