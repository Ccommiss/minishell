/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:41:12 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/29 15:24:03 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	is_a_builtin(char *cmd)
{
	if (cmd == NULL)
		return (-1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (2);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (3);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (4);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (5);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (6);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (7);
	return (0);
}

int	redir_in_built(t_env *env, char **cmd, int fd, int builtin)
{
	int	fd1;
	int	value;

	fd1 = dup(1);
	close(1);
	dup(fd);
	value = 0;
	if (builtin == 1)
		value = do_echo(cmd);
	else if (builtin == 2)
	{
		value =cd(env, cmd[1]);
		set_thepwd(env);
	}
	else if (builtin == 3)
		ft_putendl_fd(get_pwd(), 1);
	else if (builtin == 4)
		exito(cmd[1]);
	else if (builtin == 5)
		value =export_the(env, &cmd[1]);
	else if (builtin == 6)
		value = do_the_unset(env, cmd);
	else if (builtin == 7)
		value =printf_the_env(env, cmd);
	close(fd);
	dup2(fd1, 1);
	return (value);
}

int	no_cmd(int fd, int error)
{
	close(fd);
	if (error == 1)
		return (-1);
	return (0);
}

int	fork_fail(char *str, int fd, char **tenvp)
{
	perror(str);
	close(fd);
	ft_free_double_tab(tenvp);
	return (-1);
}
int	redir_in(t_env *env, t_cmd cmd, int fd, char *path)
{
	pid_t	pid;
	int		builtin;
	char	**tenvp;
	int		status;

	if (cmd.cmd_args[0] == NULL || cmd.error == 1)
		return (no_cmd(fd, cmd.error));
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if (builtin >= 1 && builtin <= 7)
		return_value = redir_in_built(env, cmd.cmd_args, fd, builtin);
	else if (builtin == 0)
	{
		tenvp = list_to_cmd(env);
		pid = fork();
		if (pid == -1)
			return (fork_fail("fork failed", fd, tenvp));
		if (pid == 0)
		{
			dup2(fd, 1);
			ft_execve(path, cmd.cmd_args, tenvp);
		}
		else
			handle_signal(CHILD_HANDLING);

		waitpid(pid, &status, 0);
		set_status(status, 1);
		ft_free_double_tab(tenvp);
	}
	close(fd);
	return (return_value);
}
