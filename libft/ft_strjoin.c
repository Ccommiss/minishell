/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:13:55 by mpochard          #+#    #+#             */
/*   Updated: 2020/11/30 00:57:12 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	init(int *i, int *k)
{
	*i = 0;
	*k = 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		k;
	char	*fi;

	init(&i, &k);
	if (!s1 || !s2)
		return (NULL);
	j = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	fi = malloc(sizeof(char *) * (j + 1));
	if (!(fi))
		return (NULL);
	while (s1[i])
	{
		fi[i] = s1[i];
		i++;
	}
	while (s2[k])
	{
		fi[i] = s2[k];
		k++;
		i++;
	}
	fi[i] = '\0';
	return (fi);
}
