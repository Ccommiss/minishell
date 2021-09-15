/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:07:39 by mpochard          #+#    #+#             */
/*   Updated: 2020/11/27 18:59:51 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_src;
	unsigned char	*ptr_dst;

	ptr_src = (unsigned char *)src;
	ptr_dst = (unsigned char *)dest;
	if (n == 0 || ptr_dst == ptr_src)
		return (dest);
	if (ptr_dst < ptr_src)
		return (ft_memcpy(dest, src, n));
	else
	{
		while (n)
		{
			ptr_dst[n - 1] = ptr_src[n - 1];
			n--;
		}
	}
	return (dest);
}
