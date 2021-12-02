/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:02:02 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/02 16:11:46 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Set status sets status accordingly to the status
**	returned by wait.
**	- If WIFSIGNALED : command interrupted by a signal
**		-> set to return value equivalent to 128 + status
**		-> displays message that process has been killed if process = 1
**		This is to avoid a multi-diplay of these messages if we have
**		several command being stopped by a ctrl C, as each child
**		process trigger a wait.
**	- If WIFEXITED : command is interrupted normally,
**		aka by exit, juste WEXITSTATUS the result
*/

void	set_status(int status, int process)
{
	if (WIFSIGNALED(status) == 1)
	{
		if (status < 128)
			status = 128 + status;
		g_return_value = status;
		if (g_return_value == 131 && process == 1)
			printf ("Quit (core dumped)\n");
		if (g_return_value == 130 && process == 1)
			printf ("\n");
	}
	else if (WIFEXITED(status) == 1)
		g_return_value = WEXITSTATUS(status);
}
