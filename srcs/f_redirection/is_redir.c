/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:08:37 by mpochard          #+#    #+#             */
/*   Updated: 2021/10/14 17:50:22 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	there_is_redir(t_env *env,t_cmd cmd)
{
	if ( cmd.io_out > 0 && cmd.io_in <= 0)
	{
		redir_in(env, cmd.cmd_args, cmd.io_out);
		return (0);
	}
	if (cmd.io_out <= 0 && cmd.io_in > 0)
	{
		printf ("ici");
		simple_redir_o(env, cmd.io_in, cmd.cmd_args);
		return (0);
	}
		return (1);
}

