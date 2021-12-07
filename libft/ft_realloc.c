/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:03:26 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/07 14:03:46 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	void	*newptr;

	newptr = malloc(newsize);
	newptr = ft_bzero(newptr, newsize);
	newptr = ft_memcpy(newptr, ptr, cursize);
	free(ptr);
	return (newptr);
}

void	**ft_realloc_double_pointer(void **ptr, size_t cursize, size_t newsize)
{
	void	**newptr;

	if (!ptr)
		return (malloc(newsize));
	newptr = malloc(newsize);
	ft_memset(newptr, '.', newsize);
	ft_memcpy(newptr, ptr, cursize);
	if (cursize != 0)
		free(ptr);
	return (newptr);
}
