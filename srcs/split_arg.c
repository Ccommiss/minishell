/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 13:25:57 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/20 13:06:05 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
 * this fonction split the arg of line with a sep like | (readline) 
 * ex : " ls -l | wc > a
 * tab[0] = ls -l
 * tab[1] = |
 * tab[2] = wc > a
 * */

int	ft_sep(char c, char sep)
{
	if ( c == sep)
		return (1);
	return (0);
}

int	ft_count_sep(char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ( ft_sep(str[i], sep) == 1)
			if ( i != 0 && ft_sep(str[i - 1], sep) == 0)
				count++;
		i++;
	}
	if (ft_sep(str[i], sep) == 0)
		count++;
	return (count);
}

char		**free_malloc(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char		*ft_strldup(char *str, char c)
{
	int		i;
	char	*fi;
	int		count;

	count = 0;
	while (str[count] && ft_sep(str[count], c) == 0)
		count++;
	if (!(fi = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	i = 0;
	while (str[i] && ft_sep(str[i], c) == 0)
	{
		fi[i] = str[i];
		i++;
	}
	fi[i] = '\0';
	return (fi);
}

// NEED TO RECODE STRNDUp
char	**ft_split_cmd(char *str, char sep, int nb)
{
	char **tab;
	int	i;
	int	j;
	int	nbr;

	i = 0;
	j = 0;
	nbr = ft_count_sep(str, sep) + nb;
	tab = malloc(sizeof(char *) * (nbr + 1));
	if (tab == NULL)
		return (NULL);
	while ( j < nbr && str[i])
	{
		while (str[i] && (ft_sep(str[i], sep) == 1))
		{
			tab[j++] = strndup(&str[i], 1);
			i++;
		}
		if (!(tab[j++] = ft_strldup(&str[i], sep)))
			return (free_malloc(tab));
		while (str[i] && (ft_sep(str[i], sep) == 0))
			i++;
	}
	tab[j] = 0;
	return (tab);
}

int main (int ac, char **av)
{
	(void)ac;
	char **test = ft_split_cmd(av[1], '|', 1);
	int i = 0;

	while ( test[i])
	{
		printf (" test %s\n",test[i]);
		i++;
	}
}
