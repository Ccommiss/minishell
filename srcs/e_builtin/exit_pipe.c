/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:17:43 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 17:35:10 by mpochard         ###   ########.fr       */
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