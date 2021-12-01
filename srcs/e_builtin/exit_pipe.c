/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:17:43 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/01 14:13:57 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_p(char *str)
{
	char	n;

	if (str == NULL)
		exit(return_value);
	n = (char)ft_atoi(str);
	exit(n);
}
