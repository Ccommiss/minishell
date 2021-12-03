/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:08:37 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/02 16:11:46 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_the_redir_in(t_env *env, t_cmd cmd, char *line)
{
	g_return_value = redir_in(env, cmd, line);
	return (0);
}

int	there_is_redir(t_env *env, t_cmd cmd, char *line)
{
	(void)line;
	if (cmd.dless == 1)
	{
		fill_thefd(cmd);
		if (g_return_value == 130)
			return (0);
		here_doc(env, cmd, 0);
		return (0);
	}
	else if (cmd.io_out == -1 || cmd.io_in == -1)
		return (0);
	else if (cmd.io_out > 0 && cmd.io_in <= 0)
		return (in_the_redir_in(env, cmd, line));
	else if (cmd.io_out <= 0 && cmd.io_in > 0)
	{
		g_return_value = simple_redir_o(env, cmd, line);
		return (0);
	}
	else if (cmd.io_out > 0 && cmd.io_in > 0)
	{
		g_return_value = both_redir(env, cmd, line);
		return (0);
	}
	return (1);
}
