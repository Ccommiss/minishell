/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:47:28 by ccommiss          #+#    #+#             */
/*   Updated: 2021/07/21 16:58:58 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	n;

	n = ft_strlen(s);
	new = (char *)malloc(n * sizeof(char) + 1);
	if (!new)
		return (NULL);
	new = ft_memcpy(new, s, n);
	new[n] = '\0';
	return (new);
}
