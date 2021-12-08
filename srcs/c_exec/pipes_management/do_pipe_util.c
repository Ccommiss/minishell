/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:34:17 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/08 16:32:10 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_cmd_dless(t_pipe piped, t_cmd *cmd)
{
	fill_thefd(*cmd);
	if (g_return_value == 130)
	{
		unlink(".here_doc");
		close_all_p(piped.pipefd, piped.nbr_p);
		free(piped.pipefd);
		free(piped.pid);
		if (cmd->io_out > 0)
			close(cmd->io_out);
		if (cmd->io_in > 0)
			close(cmd->io_in);
		return (-1);
	}
	return (0);
}
