/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:41:59 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/12 17:42:59 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * cmd_suffix is the -n
 *	this fct is for check is the sec arg of echo is -n or not 
 *	-nnnnm dont work but -nnnnnn  work !!!
 */
int	check_echo(char *cmd_suffix)
{
	int	i;

	i = 0;
//	printf("cmd_suffix %s\n", cmd_suffix);
	if (cmd_suffix[i] == '-')
	{
		i++;
	if ( cmd_suffix[i] == '\0')
		return (0);
	}
		else
		return (0);
	while (cmd_suffix[i] == 'n')
		i++;
	if (cmd_suffix[i] != 'n' && cmd_suffix[i] != '\0')
		return (0);
	else
		return (1);
	return (0);
}

int		count_double_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
/*
 * need to know is echo have arg or not
 * -in case of echo without arg the program should display \n 
 * -in case of echo -n withouth arg the program should display nothing
 *  -the program begin at i = 1 because i = 0 is echo 
 *  - need to tchek the nbr of arg of echo, security of segfault
 */
int		do_echo(char **cmd_suffix)
{
	int	i;
	int	count;

	i = 1;
	count = count_double_tab(cmd_suffix); 
	if (count > 1 && check_echo(cmd_suffix[i]) == 1)
	{
		i++;
		if (count > 2)
		{
		while (cmd_suffix[i])
		{
			write(1, cmd_suffix[i], ft_strlen(cmd_suffix[i]));
			if ( i < count -1)
				write(1," ", 1);
			i++;
		}
	}
	}
	else
	{
		if (count > 1)
		{
		while (cmd_suffix[i])
		{
			write(1, cmd_suffix[i], ft_strlen(cmd_suffix[i]));
			if ( i < count -1)
				write(1," ", 1);
			i++;
		}
		}
		write(1, "\n", 1);
	}
	return (0);
}
