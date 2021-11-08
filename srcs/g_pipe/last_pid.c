/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:28:47 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/08 15:10:46 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redir_l(t_cmd cmd, int *pipefd, int nbr_p, int redir)
{
	if (cmd.cmd_args[0] == NULL || cmd.error == 1)
		exit(0);
	if (redir == 0)
	{
		dup2(pipefd[nbr_p - 2], 0);
		close_all_p(pipefd, nbr_p);
	}
	else if (redir == 1)
	{
		dup2(cmd.io_out, 1);
		dup2(pipefd[nbr_p - 2], 0);
		close_all_p(pipefd, nbr_p);
	}
	else if (redir == 2)
	{
		dup2(cmd.io_in, 0);
		close_all_p(pipefd, nbr_p);
	}
	else if (redir == 4)
	{
		dup2(cmd.io_in, 0);
		dup2(cmd.io_out, 1);
		close_all_p(pipefd, nbr_p);
	}
}

int	last_pid(t_cmd cmd, t_env *env, int *pipefd, int nbr_p)
{
	char	**tenvp;
	int		redir;
	int		builtin;

	tenvp = list_to_cmd(env);
	redir = which_redir(cmd);
	builtin = is_a_builtin(cmd.cmd_args[0]);
	do_redir_l(cmd, pipefd, nbr_p, redir);
	if (builtin >= 1 && builtin <= 7)
	{
		exec_builtin(env, cmd.cmd_args, builtin);
		exit(0);
	}
	else if (builtin == 0)
		ft_execve(cmd.cmdp, cmd.cmd_args, tenvp);
	return (0);
}
