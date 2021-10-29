/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:08:37 by mpochard          #+#    #+#             */
/*   Updated: 2021/10/20 11:15:28 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	there_is_redir(t_env *env,t_cmd cmd)
{
	(void)env;
	int	fd;
	if ( cmd.dless == 1)
	{
		fd = fill_thefd(cmd);
		here_doc(env, cmd, fd);
		return (0);
	}
	else if (cmd.io_out == -1 || cmd.io_in == -1)
		return (0);
	else if ( cmd.io_out > 0 && cmd.io_in <= 0)
	{
		redir_in(env, cmd.cmd_args, cmd.io_out, cmd.cmdp);
		return (0);
	}
	else if (cmd.io_out <= 0 && cmd.io_in > 0)
	{
		simple_redir_o(env, cmd.io_in, cmd.cmd_args, cmd.cmdp);
		return (0);
	}
	else if (cmd.io_out > 0 && cmd.io_in > 0)
	{
		both_redir(env, cmd, cmd.io_in , cmd.io_out);
		return (0);
	}
	return (1);
}

