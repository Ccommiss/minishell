/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:04:10 by mpochard          #+#    #+#             */
/*   Updated: 2020/11/23 01:18:34 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		k;
	size_t		j;
	char		*l1;
	char		*b1;

	b1 = (char *)haystack;
	l1 = (char *)needle;
	k = ft_strlen(l1);
	i = 0;
	if (k == 0)
		return (b1);
	while (i < len && b1[i])
	{
		k = 0;
		j = k + i;
		while (j++ < len && b1[k + i] == l1[k])
		{
			if (l1[k + 1] == '\0')
				return (&b1[i]);
			k++;
		}
		i++;
	}
	return (NULL);
}
