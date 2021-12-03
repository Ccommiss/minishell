/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 02:30:55 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/03 14:03:07 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*s1;
	char	*fi;

	if (!s)
		return (NULL);
	s1 = (char *)s;
	fi = NULL;
	i = 0;
	fi = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!(fi))
		return (NULL);
	while (s1[i])
	{
		fi[i] = s1[i];
		i++;
	}
	fi[i] = '\0';
	return ((char *)fi);
}
