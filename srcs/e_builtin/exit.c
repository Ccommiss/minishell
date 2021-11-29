/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:17:43 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/26 11:00:11 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exito(char	*str)//, t_cmd *cmd, t_env *env)
{
	char n;

	if (isatty(1) && isatty(0))
		write(1, "exit\n", 5);
	if (str == NULL)
		exit(return_value);
	n = (char)ft_atoi(str);
	exit(n);
}
