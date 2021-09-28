/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_int_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:24:12 by ccommiss          #+#    #+#             */
/*   Updated: 2021/06/22 12:55:11 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_malloc_int_pointer(int size, int	**ptr)
{
	*ptr = (int *)malloc(sizeof(int) * size);
	if (!*ptr)
		return (0);
	return (1);
}
