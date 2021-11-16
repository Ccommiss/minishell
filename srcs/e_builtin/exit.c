/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:17:43 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/16 16:04:10 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exito(char	*str)
{
	char n;
	
	if (isatty(1) && isatty(0))
		write(1, "exit\n", 5);
	if (str == NULL)
		exit(g_utils.return_value);
	n = (char)ft_atoi(str);
	exit(n);
}
