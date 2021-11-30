/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:41:12 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 18:22:55 by mpochard         ###   ########.fr       */
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

int	redir_in_built(t_env *env, t_cmd cmd, int builtin, char *line)
{
	int	fd1;
	int	value;

	(void)line;
	fd1 = dup(1);
	close(1);
	dup(cmd.io_out);
	value = 0;
	if (builtin >= 1 && builtin <= 7)
		built(env, cmd, &value, builtin);
	close(cmd.io_out);
	dup2(fd1, 1);
	return (value);
}

void	inside_the_pid(t_cmd cmd, char **tenvp)
{
	dup2(cmd.io_out, 1);
	ft_execve(cmd.cmdp, cmd.cmd_args, tenvp);
}

int	redir_in(t_env *env, t_cmd cmd, char *line)
{
	pid_t	pid;
	int		builtin;
	char	**tenvp;
	int		status;

	if (cmd.cmd_args[0] == NULL || cmd.error == 1)
		return (no_cmd(cmd.io_out, cmd.error));
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if (builtin >= 1 && builtin <= 7)
		return_value = redir_in_built(env, cmd, builtin, line);
	else if (builtin == 0)
	{
		tenvp = list_to_cmd(env);
		pid = fork();
		if (pid == -1)
			return (fork_fail("fork failed", cmd.io_out, tenvp));
		if (pid == 0)
			inside_the_pid(cmd, tenvp);
		handle_signal(CHILD_HANDLING);
		waitpid(pid, &status, 0);
		set_status(status, 1);
		ft_free_double_tab(tenvp);
	}
	close(cmd.io_out);
	return (return_value);
}