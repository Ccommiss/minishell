/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 13:25:57 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/20 13:38:53 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
 * this fonction split the arg of line with a sep like | (readline) 
 * ex : " ls -l | wc > a
 */
 
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

char	**ft_split_cmd(char *str, char sep, t_arg op)
{
	char **tab;
	int	i;
	int	nbr;

	i = 0;
	nbr = ft_count_sep(str, sep) + op.nb_pipe;
	tab = malloc(sizeof(char *) * (nbr + 1));
	if (tab == NULL)
		return (NULL);
	while (str[i])
	{
	}

	return (tab);
}
