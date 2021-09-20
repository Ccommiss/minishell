/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:10:04 by mpochard          #+#    #+#             */
/*   Updated: 2020/11/30 17:33:44 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		destlen;
	char		*s1;

	i = 0;
	s1 = (char *)src;
	if (dstsize == 0)
		return (ft_strlen(s1));
	destlen = ft_strlen(dst);
	if (destlen > dstsize)
		return (dstsize + ft_strlen(s1));
	if (dstsize > destlen && dstsize > 0)
	{
		while (s1[i] && i < (dstsize - destlen - 1))
		{
			dst[destlen + i] = s1[i];
			i++;
		}
		dst[destlen + i] = '\0';
	}
	return (destlen + ft_strlen(s1));
}
