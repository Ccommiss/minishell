/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:41:18 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/07 12:11:39 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	in_the_pid(t_cmd cmd, char **tenvp)
{
	dup2(cmd.io_in, 0);
	ft_execve(cmd.cmdp, cmd.cmd_args, tenvp);
}

int	simple_redir_o(t_env *env, t_cmd cmd, char *line)
{
	pid_t	pid;
	int		builtin;
	char	**tenvp;
	int		status;

	if (cmd.cmd_args[0] == NULL || cmd.error == 1)
		return (no_cmd(cmd.io_in, cmd.error));
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if ((builtin >= 1 && builtin <= 7) && cmd.io_in > -1)
		g_return_value = redir_out_built(env, cmd, builtin, line);
	else if (builtin == 0 && cmd.io_in > -1)
	{
		tenvp = list_to_cmd(env);
		pid = fork();
		if (pid == -1)
			return (fork_fail("fork failed", cmd.io_in, tenvp));
		else if (pid == 0)
			in_the_pid(cmd, tenvp);
		handle_signal(CHILD_HANDLING);
		waitpid(pid, &status, 0);
		set_status(status, 1);
		ft_free_double_tab(tenvp);
	}
	close(cmd.io_in);
	return (g_return_value);
}

void	in_the_pid_doubl(t_cmd cmd, char **tenvp)
{
	dup2(cmd.io_out, 1);
	dup2(cmd.io_in, 0);
	ft_execve(cmd.cmdp, cmd.cmd_args, tenvp);
}

void	close_the(t_cmd cmd)
{
	close(cmd.io_in);
	close(cmd.io_out);
}

int	both_redir(t_env *env, t_cmd cmd, char *line)
{
	int		builtin;
	pid_t	pid;
	char	**tenvp;
	int		status;

	if (cmd.cmd_args[0] == NULL || cmd.error == 1)
		return (no_cmd_d(cmd.io_in, cmd.io_out, cmd.error));
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if ((builtin >= 1 && builtin <= 7) && cmd.io_in >= -1 && cmd.io_out >= -1)
		g_return_value = redir_double_built(env, cmd, builtin, line);
	else if (builtin == 0 && (cmd.io_in >= -1 && cmd.io_out >= -1))
	{
		tenvp = list_to_cmd(env);
		pid = fork();
		if (pid == -1)
			return (fork_fail_d("fork failed", cmd.io_in, cmd.io_out, tenvp));
		if (pid == 0)
			in_the_pid_doubl(cmd, tenvp);
		handle_signal(CHILD_HANDLING);
		waitpid(pid, &status, 0);
		set_status(status, 1);
		ft_free_double_tab(tenvp);
	}
	close_the(cmd);
	return (g_return_value);
}
