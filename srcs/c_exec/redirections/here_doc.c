/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:11:36 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/06 13:20:38 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_cmd_here(int in, int out)
{
	if (in > 0)
		close(in);
	if (out > 0)
		close(out);
	unlink(".here_doc");
	return ;
}

void	the_rest_built(t_env *env, t_cmd cmd, int builtin)
{
	if (builtin == 3)
	{
		ft_putendl_fd(get_pwd(), 1);
		g_return_value = 0;
	}
	else if (builtin == 4)
		exito(cmd.cmd_args, &cmd, env, NULL);
	else if (builtin == 5)
		g_return_value = export_the(env, &cmd.cmd_args[1]);
	else if (builtin == 6)
		g_return_value = do_the_unset(env, cmd.cmd_args);
	else if (builtin == 7)
		g_return_value = printf_the_env(env, cmd.cmd_args);
}

void	redir_here_built(t_env *env, t_cmd cmd, int builtin)
{
	int	fd1;

	if (cmd.io_out > 0)
	{
		fd1 = dup(1);
		close(1);
		dup(cmd.io_out);
	}
	if (builtin == 1)
		g_return_value = do_echo(cmd.cmd_args);
	else if (builtin == 2)
	{
		g_return_value = cd(env, &cmd.cmd_args[1]);
		set_thepwd(env);
	}
	else if (builtin >= 3 && builtin <= 7)
		the_rest_built(env, cmd, builtin);
	if (cmd.io_out > 0)
	{
		close(cmd.io_out);
		dup2(fd1, 1);
	}
	if (cmd.io_in > 0)
		close(cmd.io_in);
}

void	do_the_dup(int out, int fd, t_cmd cmd, char **tenvp)
{
	fd = open(".here_doc", O_RDWR, 0666);
	if (out > 0)
		dup2(out, 1);
	dup2(fd, 0);
	ft_execve(cmd.cmdp, cmd.cmd_args, tenvp);
}

void	here_doc(t_env *env, t_cmd cmd, int fd)
{
	int		builtin;
	int		status;
	pid_t	pid;
	char	**tenvp;

	if (cmd.cmd_args[0] == NULL || cmd.error == 1)
		return (no_cmd_here(cmd.io_in, cmd.io_out));
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if ((builtin >= 1 && builtin <= 7))
		redir_here_built(env, cmd, builtin);
	else if (builtin == 0)
	{
		tenvp = list_to_cmd(env);
		pid = fork();
		if (pid == -1)
			fork_fail_d("fork failed", cmd.io_out, cmd.io_in, tenvp);
		else if (pid == 0)
			do_the_dup(cmd.io_out, fd, cmd, tenvp);
		handle_signal(CHILD_HANDLING);
		waitpid(pid, &status, 0);
		set_status(status, 1);
		ft_free_double_tab(tenvp);
	}
	unlink(".here_doc");
}
