/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 13:25:57 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/19 15:16:47 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/minishell.h"

#include <stdio.h>
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
int	main (int ac, char **av)
{
	(void)ac;
	printf ("mot %d\n", ft_count_sep(av[1], '|'));
}

/*
	char	**ft_split_cmd(char *str, char sep)
{
	char **tab;
	int	i;
	int	nbr;

	i = 0;
	nbr = ft_count_sep(str, sep);
	tab = malloc(sizeof(char *) * (nbr + 1));
	if (tab == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == */
