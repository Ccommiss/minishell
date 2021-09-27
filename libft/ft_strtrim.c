/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:41:49 by mpochard          #+#    #+#             */
/*   Updated: 2021/01/16 12:31:03 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*fi;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	if (*s1 < 0)
		j = ft_strlen(s1) - 0;
	else
		j = (ft_strlen(s1) - 1);
	while (s1[i] && ft_charset(s1[i], set) == 1)
		i++;
	while ((j > i) && ft_charset(s1[j], set) == 1)
		j--;
	fi = malloc(sizeof(*fi) * (j - i) + 1);
	if (!(fi))
		return (NULL);
	fi = ft_substr(s1, i, (j - i) + 1);
	return (fi);
}
