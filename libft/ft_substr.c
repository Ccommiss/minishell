/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:45:53 by mpochard          #+#    #+#             */
/*   Updated: 2020/11/30 00:54:18 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*error(void)
{
	char	*stp;

	stp = malloc(sizeof(char));
	if (!(stp))
		return (NULL);
	stp[0] = 0;
	return (stp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*stp;
	char		*s1;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		stp = error();
		return (stp);
	}
	s1 = malloc(sizeof(char) * len + 1);
	if (!(s1))
		return (NULL);
	while (i < start)
		i++;
	while (s[i] && j < len)
		s1[j++] = s[i++];
	s1[j] = '\0';
	return (s1);
}
