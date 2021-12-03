/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:28:44 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 11:51:18 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redir_o(t_cmd cmd, int i, t_pipe piped, int redir)
{
	if (cmd.cmd_args[0] == NULL || cmd.error == 1)
		exit(0);
	if (redir == 0)
	{
		dup2(piped.pipefd[i + (i - 2)], 0);
		dup2(piped.pipefd[i + i + 1], 1);
	}
	else if (redir == 1)
	{
		dup2(piped.pipefd[i + (i - 2)], 0);
		dup2(cmd.io_out, 1);
	}
	else if (redir == 2)
	{
		dup2(piped.pipefd[i + i + 1], 1);
		dup2(cmd.io_in, 0);
	}
	else if (redir == 4)
	{
		dup2(cmd.io_in, 0);
		dup2(cmd.io_out, 1);
	}
	close_all_p(piped.pipefd, piped.nbr_p);
}

int	other_pid(t_cmd cmd, t_env *env, t_pipe piped, int i)
{
	char	**tenvp;
	int		redir;
	int		builtin;

	redir = which_redir(cmd);
	tenvp = list_to_cmd(env);
	builtin = is_a_builtin(cmd.cmd_args[0]);
	do_redir_o(cmd, i, piped, redir);
	if (builtin >= 1 && builtin <= 7)
	{
		exec_builtin(env, cmd.cmd_args, builtin);
	}
	else if (builtin == 0)
		ft_execve(cmd.cmdp, cmd.cmd_args, tenvp);
	return (0);
}
