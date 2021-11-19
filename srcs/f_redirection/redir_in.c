/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:41:12 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/19 13:15:03 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	is_a_builtin(char *cmd)
{
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

void	redir_in_built(t_env *env, char **cmd, int fd, int builtin)
{
	int	fd1;

	fd1 = dup(1);
	close(1);
	dup(fd);
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
		exito(cmd[1]);
	else if (builtin == 5)
		export_the(env, &cmd[1]);
	else if (builtin == 6)
		do_the_unset(env, cmd);
	else if (builtin == 7)
		printf_the_env(env, NULL);
	close(fd);
	dup2(fd1, 1);
}

void	no_cmd(int fd)
{
	close(fd);
	return ;
}

void	fork_fail(char *str, int fd, char **tenvp)
{
	perror(str);
	close(fd);
	ft_free_double_tab(tenvp);
	return ;
}

void	redir_in(t_env *env, t_cmd cmd, int fd, char *path)
{
	pid_t	pid;
	int		builtin;
	char	**tenvp;

	if (cmd.cmd_args[0] == NULL || cmd.error == 1)
		return (no_cmd(fd));
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if (builtin >= 1 && builtin <= 7)
		redir_in_built(env, cmd.cmd_args, fd, builtin);
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
		waitpid(pid, NULL, 0);
		ft_free_double_tab(tenvp);
	}
	close(fd);
}
