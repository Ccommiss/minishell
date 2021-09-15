/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:29:05 by mpochard          #+#    #+#             */
/*   Updated: 2020/11/30 15:44:39 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_charset(char str, char c)
{
	if (str == c)
		return (1);
	return (0);
}

static int		ft_countword(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (i && ft_charset(str[i], c) == 1)
			if (i && ft_charset(str[i - 1], c) == 0)
				count++;
		i++;
	}
	if (i && ft_charset(str[i - 1], c) == 0)
		count++;
	return (count);
}

static char		*ft_strldup(char *str, char c)
{
	int		i;
	char	*fi;
	int		count;

	count = 0;
	while (str[count] && ft_charset(str[count], c) == 0)
		count++;
	if (!(fi = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	i = 0;
	while (str[i] && ft_charset(str[i], c) == 0)
	{
		fi[i] = str[i];
		i++;
	}
	fi[i] = '\0';
	return (fi);
}

static char		*free_malloc(char **tabfi)
{
	while (*tabfi)
	{
		free(*tabfi);
		tabfi++;
	}
	free(tabfi);
	return (NULL);
}

char			**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tabfi;
	char	*s1;

	if (s == NULL)
		return (NULL);
	s1 = (char *)s;
	k = ft_countword(s1, c);
	if (!(tabfi = malloc(sizeof(char *) * (k + 1))))
		return (NULL);
	j = 0;
	i = 0;
	while (j < k && s1[i])
	{
		while (s1[i] && (ft_charset(s1[i], c) == 1))
			i++;
		if (!(tabfi[j++] = (ft_strldup(&s1[i], c))))
			free_malloc(tabfi);
		while (s[i] && (ft_charset(s1[i], c)) == 0)
			i++;
	}
	tabfi[j] = 0;
	return (tabfi);
}
