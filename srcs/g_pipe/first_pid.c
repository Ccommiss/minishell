/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:05:45 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/24 11:56:19 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * redir = 0 no redir
 * redir = 1 redir >
 * redir = 2 redir <
 * redir 3 <<
 * redir 4 ><
 */

void	do_redir_f(t_cmd cmd, int *pipefd, int nbr_p, int redir)
{
	if ((cmd.cmd_args[0] == NULL) || (cmd.error == 1))
		exit(0);
	if (redir == 0)
	{
		dup2(pipefd[1], 1);
		close_all_p(pipefd, nbr_p);
	}
	else if (redir == 1)
	{
		dup2(cmd.io_out, 1);
		close_all_p(pipefd, nbr_p);
	}
	else if (redir == 2)
	{
		dup2(cmd.io_in, 0);
		dup2(pipefd[1], 1);
		close_all_p(pipefd, nbr_p);
	}
	else if (redir == 4)
	{
		dup2(cmd.io_in, 0);
		dup2(cmd.io_out, 1);
		close_all_p(pipefd, nbr_p);
	}
}

void	exec_builtin(t_env *env, char **cmd, int builtin)
{
	if (builtin == 1)
		do_echo(cmd);
	else if (builtin == 2)
	{
		cd(env, cmd[1]);
		set_thepwd(env);
	}
	else if (builtin == 3)
		ft_putendl_fd(get_pwd(), 1);
	else if (builtin == 4)
	{
		exit_p(cmd[1]);
		return ;
	}
	else if (builtin == 5)
		export_the(env, &cmd[1]);
	else if (builtin == 6)
		do_the_unset(env, cmd);
	else if (builtin == 7)
		printf_the_env(env, cmd);
	exit(0);
}

int	first_pid(t_cmd cmd, t_env *env, int *pipefd, int nbr_p )
{
	int		builtin;
	int		redir;
	char	**tenvp;

	redir = which_redir(cmd);
	tenvp = list_to_cmd(env);
	builtin = is_a_builtin(cmd.cmd_args[0]);
	do_redir_f(cmd, pipefd, nbr_p, redir);
	if (builtin >= 1 && builtin <= 7)
	{
		exec_builtin(env, cmd.cmd_args, builtin);
	}
	else if (builtin == 0)
		ft_execve(cmd.cmdp, cmd.cmd_args, tenvp);
	return (0);
}
