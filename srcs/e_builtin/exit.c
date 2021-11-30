/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:17:43 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 17:35:29 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exito(char	*str, t_cmd *cmd, t_env *env, char *line)
{
	char	n;

	(void)line;
	(void)cmd;
	if (isatty(1) && isatty(0))
		write(1, "exit\n", 5);
	clean_env(env);
	if (str == NULL)
		exit(return_value);
	n = (char)ft_atoi(str);
	exit(n);
}