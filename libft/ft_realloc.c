/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:25:16 by elisehautef       #+#    #+#             */
/*   Updated: 2021/10/22 14:54:45 by ehautefa         ###   ########.fr       */
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
