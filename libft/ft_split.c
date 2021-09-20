/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:29:05 by mpochard          #+#    #+#             */
/*   Updated: 2021/06/09 14:38:26 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charset(char str, char c)
{
	if (str == c)
		return (1);
	return (0);
}

static int	ft_countword(char *str, char c)
{
	int	i;
	int	count;

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

static char	*ft_strldup(char *str, char c)
{
	int		i;
	char	*fi;
	int		count;

	count = 0;
	while (str[count] && ft_charset(str[count], c) == 0)
		count++;
	fi = malloc(sizeof(char) * (count + 1));
	if (!(fi))
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

static char	*free_malloc(char **tabfi)
{
	while (*tabfi)
	{
		free(*tabfi);
		tabfi++;
	}
	free(tabfi);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	t_split	utils;
	char	**tabfi;

	if (s == NULL)
		return (NULL);
	utils.s1 = (char *)s;
	utils.k = ft_countword(utils.s1, c);
	tabfi = malloc(sizeof(char *) * (utils.k + 1));
	if (!(tabfi))
		return (NULL);
	utils.j = 0;
	utils.i = 0;
	while (utils.j < utils.k && utils.s1[utils.i])
	{
		while (utils.s1[utils.i] && (ft_charset(utils.s1[utils.i], c) == 1))
			utils.i++;
		tabfi[utils.j] = (ft_strldup(&utils.s1[utils.i], c));
		if (tabfi[utils.j] == NULL)
			free_malloc(tabfi);
		utils.j++;
		while (s[utils.i] && (ft_charset(utils.s1[utils.i], c)) == 0)
			utils.i++;
	}
	tabfi[utils.j] = 0;
	return (tabfi);
}
