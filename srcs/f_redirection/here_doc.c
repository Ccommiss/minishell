/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:11:36 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/26 11:07:16 by ccommiss         ###   ########.fr       */
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
		ft_putendl_fd(get_pwd(), 1);
	else if (builtin == 4)
		exito(cmd.cmd_args[1]);
	else if (builtin == 5)
		export_the(env, &cmd.cmd_args[1]);
	else if (builtin == 6)
		do_the_unset(env, cmd.cmd_args);
	else if (builtin == 7)
		printf_the_env(env, cmd.cmd_args);
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
		do_echo(cmd.cmd_args);
	else if (builtin == 2)
	{
		cd(env, cmd.cmd_args[1]);
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

void	do_the_dup(int out, int fd)
{
	if (out > 0)
		dup2(out, 1);
	dup2(fd, 0);
}
void	here_doc(t_env *env, t_cmd cmd, int fd)
{
	int		builtin;
	int		status;
	pid_t	pid;
	char	**tenvp;

	if (cmd.cmd_args[0] == NULL) // mettre en place si ya un pb t rentre pas dedans)
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
		{
			fd = open(".here_doc", O_RDWR, 0666);
			do_the_dup(cmd.io_out, fd);
			ft_execve(cmd.cmdp, cmd.cmd_args, tenvp);
		}
		waitpid(pid, &status, 0);
		set_status(status, 0);
	}
	unlink(".here_doc");
}
