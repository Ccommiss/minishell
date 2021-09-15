/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:15:34 by mpochard          #+#    #+#             */
/*   Updated: 2020/11/27 15:22:49 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s1;
	int		k;

	s1 = (char *)s;
	k = (ft_strlen(s1));
	while (k > -1)
	{
		if (s[k] == ((unsigned char)c))
			return (&s1[k]);
		k--;
	}
	return (NULL);
}
