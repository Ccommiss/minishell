/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:32:10 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 17:24:33 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * util for swap  when we print the export
 * because export is print with ascii order
 */

void	ft_charswap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

/*
 * my export is in a tab so i have to calculate the nbr of line in export
 */
int	nb_export(t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		if ((env->visible == 0 || env->visible == 1))
		{
			i++;
		}
		env = env->next;
	}
	return (i);
}

char	**free_tab_index(char **tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(tab[j]);
		j++;
	}
	return (NULL);
}

void	print(char **exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		printf("declare -x %s\n", exp[i]);
		i++;
	}
}

/*
 * we put the right var in the tab so we can print just the tab 
 */

int	print_the_export(t_env *env)
{
	char	**exp;
	int		i;
	int		j;
	int		nbr;

	i = 0;
	exp = fill_thexport(env);
	if (exp == NULL)
		return (-1);
	nbr = nb_export(env);
	while (i < nbr)
	{
		j = 0;
		while (j < nbr - 1 - i)
		{
			if (strcmp(exp[j], exp[j + 1]) > 0)
				ft_charswap(&exp[j], &exp[j + 1]);
			j++;
		}
		i++;
	}
	print(exp);
	ft_free_double_tab(exp);
	return (0);
}