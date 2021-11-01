/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:25:16 by elisehautef       #+#    #+#             */
/*   Updated: 2021/11/01 16:29:17 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (ptr == NULL || size <= 0)
		return (NULL);
	new = malloc(size * sizeof(void));
	if (new == NULL)
		return (NULL);
	free(ptr);
	ptr = NULL;
	return (new);
}
