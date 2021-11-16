/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:08:37 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/11 10:40:07 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	there_is_redir(t_env *env, t_cmd cmd)
{
//	printf("cmd.error%d\n", cmd.error);
	if (cmd.error == 1)
		return (0);
	if (cmd.dless == 1)
	{
		fill_thefd(cmd);
		here_doc(env, cmd, 0);
		return (0);
	}
	else if (cmd.io_out == -1 || cmd.io_in == -1)
		return (0);
	else if (cmd.io_out > 0 && cmd.io_in <= 0)
	{
		redir_in(env, cmd, cmd.io_out, cmd.cmdp);
		return (0);
	}
	else if (cmd.io_out <= 0 && cmd.io_in > 0)
	{
		simple_redir_o(env, cmd.io_in, cmd, cmd.cmdp);
		return (0);
	}
	else if (cmd.io_out > 0 && cmd.io_in > 0)
	{
		both_redir(env, cmd, cmd.io_in, cmd.io_out);
		return (0);
	}
	return (1);
}
