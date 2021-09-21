/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 13:25:57 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/21 17:31:25 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
 * this fonction split the arg of line  with space \t \v \r  (readline) 
 * */

int	ft_sep(char c)
{
	if (ft_isin(c," \n\v\f\r") == 1)
		return (1);
	return (0);
}

int	ft_count_word(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
			if ( i == 0 && (str[i] == '\"'))
			{
				i++;
				while (str[i] && str[i] != '\"')
				{
					i++;
				}
					if ( str[i] == '\"')
				{
					count++;
				}
			}
		if ( i && ft_sep(str[i - 1]) == 1)
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				i++;
				while (str[i] && (str[i] != '\'' || str[i] != '\"'))
					i++;
				if (str[i] == '\'' || str[i] == '\"')
				{
					i++;
					printf("123\n");
					count++;
				}
			}
			}
		if ( ft_sep(str[i]) == 1)
			if ( i != 0 && ft_sep(str[i - 1]) == 0)
				count++;
		i++;
	}
	if (str[i - 1] != '\"' && ft_sep(str[i -1]) == 0)
		count++;
	return (count);
}
/*
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
	while (str[count] && ft_sep(str[count]) == 0)
		count++;
	if (!(fi = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	i = 0;
	while (str[i] && ft_sep(str[i]) == 0)
	{
		fi[i] = str[i];
		i++;
	}
	fi[i] = '\0';
	return (fi);
}

// NEED TO RECODE STRNDUp
char	**ft_split_cmd(char *str)
{
	char **tab;
	int	i;
	int	j;
	int	nbr;

	i = 0;
	j = 0;
	nbr = ft_count_sep(str);
	tab = malloc(sizeof(char *) * (nbr + 1));
	if (tab == NULL)
		return (NULL);
	while ( j < nbr && str[i])
	{

	}
	tab[j] = 0;
	return (tab);
}
*/
int main (int ac, char **av)
{
	(void)ac;
	(void)av;
	char	*line;

	line = readline("hi>");
	printf("i %d\n", ft_count_word(line));
/*	char **test = ft_split_cmd(av[1]);
	int i = 0;

	while ( test[i])
	{
		printf (" test %s\n",test[i]);
		i++;
	}*/
}
