/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_char_pointer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:23:55 by ccommiss          #+#    #+#             */
/*   Updated: 2021/07/21 17:02:39 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_malloc_char_pointer(int size, char **ptr)
{
	*ptr = (char *)malloc(sizeof(char) * size);
	if (!*ptr)
		return (0);
	return (1);
}
