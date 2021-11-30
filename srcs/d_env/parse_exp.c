/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:27:05 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 17:24:04 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * util to see if there is a unvalible char in the string of export 
 * like 12 in first char or - or $ ect..
 */
int	parse_cmd_suf(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 1 || str[0] == '_')
		i++;
	else
	{
		printf("export: « %s » : identifiant non valable\n", str);
		return (-1);
	}
	while (ft_isalnum(str[i]) == 1 || str[i] == '_')
		i++;
	if (str[i] == '+' && str[i + 1] == '=')
		return (0);
	else if (str[i] == '=')
		return (0);
	else if (str[i] == '\0')
		return (0);
	else
	{
		printf("export: « %s » : identifiant non valable\n", str);
		return (-1);
	}
	return (0);
}

/*
 * export a+=b its not the same comportement of 
 * there normal export so i have to parse 
*/

int	ft_parse_concate(char *cmd_suffix)
{
	int	i;

	i = 0;
	while (cmd_suffix[i])
	{
		if (cmd_suffix[i] == '+')
		{
			i++;
			if (cmd_suffix[i] == '=')
				return (1);
		}
		i++;
	}
	return (0);
}

int	find_value_egal(char *cmd_suffix)
{
	int	egal;

	if (ft_parse_concate(cmd_suffix) == 1)
		egal = 2;
	else if (ft_isin('=', cmd_suffix) == 1)
		egal = 1;
	else
		egal = 0;
	return (egal);
}