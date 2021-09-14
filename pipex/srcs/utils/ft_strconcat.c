/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 15:46:55 by ccommiss          #+#    #+#             */
/*   Updated: 2021/07/22 15:46:56 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strconcat(char *s1, char *s2, int size)
{
	char		*concat;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!ft_malloc_char_pointer(size + 1, &concat))
		return (NULL);
	if (s1)
		while (s1[i])
			*concat++ = s1[i++];
	if (s2)
		while (s2[j])
			*concat++ = s2[j++];
	*(concat) = '\0';
	return (concat - size);
}
