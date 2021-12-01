/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:21:10 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/01 14:12:03 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_the_cmd(char *cmd_suffix)
{
	int	i;

	if (ft_isalpha(cmd_suffix[0]) == 0 && cmd_suffix[0] != '_')
	{
		printf(" unset: '%s': not a valid identifier\n", cmd_suffix);
		return (-1);
	}
	i = 1;
	while (cmd_suffix[i])
	{
		if (ft_isalnum(cmd_suffix[i]) == 0 && cmd_suffix[i] != '_')
		{
			printf(" unset: '%s': not a valid identifier\n", cmd_suffix);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	case_first(t_env *tmp)
{
	tmp->visible = -3;
	return (0);
}
