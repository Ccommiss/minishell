/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:17:43 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/02 16:11:46 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_p(char **cmd_suff)
{
	char	n;
	int		count;

	if (cmd_suff[1] == NULL)
		exit(g_return_value);
	count = count_double_tab(cmd_suff);
	if (count > 2)
	{
		if (error_count(cmd_suff[1], NULL, 0) == 1)
			return ;
	}
	if (if_num(cmd_suff[1]) == 0)
		error_num(cmd_suff[1], NULL, 0);
	n = (char)ft_atoi(cmd_suff[1]);
	exit(n);
}
