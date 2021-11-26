/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:41:18 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/26 11:07:29 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	simple_redir_o(t_env *env, int fd, t_cmd cmd, char *path)
{
	pid_t	pid;
	int		builtin;
	char	**tenvp;
	int		status;

	if (cmd.cmd_args[0] == NULL || cmd.error == 1)
		return (no_cmd(fd, cmd.error));
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if ((builtin >= 1 && builtin <= 7) && fd > -1)
		return_value = redir_out_built(env, cmd.cmd_args, fd, builtin);
	else if (builtin == 0 && fd > -1)
	{
		tenvp = list_to_cmd(env);
		pid = fork();
		if (pid == -1)
			return (fork_fail("fork failed", fd, tenvp));
		else if (pid == 0)
		{
			dup2(fd, 0);
			ft_execve(path, cmd.cmd_args, tenvp);
		}
		waitpid(pid, &status, 0);
		set_status(status, 0);
		ft_free_double_tab(tenvp);
	}
	close(fd);
	return (return_value);
}

int		both_redir(t_env *env, t_cmd cmd, int in, int out)
{
	int		builtin;
	pid_t	pid;
	char	**tenvp;
	int		status;

	if (cmd.cmd_args[0] == NULL || cmd.error == 1)
		return (no_cmd_d(in, out, cmd.error));
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if ((builtin >= 1 && builtin <= 7) && in >= -1 && out >= -1)
		return_value = redir_double_built(env, cmd, builtin);
	else if (builtin == 0 && (in >= -1 && out >= -1))
	{
		tenvp = list_to_cmd(env);
		pid = fork();
		if (pid == -1)
			return (fork_fail_d("fork failed", in, out, tenvp));
		if (pid == 0)
		{
			dup2(out, 1);
			dup2(in, 0);
			ft_execve(cmd.cmdp, cmd.cmd_args, tenvp);
		}
		waitpid(pid, &status, 0);
		set_status(status, 0);
	}
	close(out);
	close(in);
	return (return_value);
}
