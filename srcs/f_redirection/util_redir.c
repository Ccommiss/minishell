/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:41:40 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 18:12:51 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(char *path, char **cmd, char **tenvp)
{
	handle_signal(CHILD);
	if (path == NULL)
	{
		if (execve(cmd[0], cmd, tenvp) == -1)
		{
			write(2, "Minishell: ", 11);
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, " : commande introuvable\n", 24);
			exit(127);
		}
	}
	else
	{
		if (execve(path, cmd, tenvp) == -1)
		{
			write(2, "Minishell: ", 11);
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, " : commande introuvable\n", 24);
			exit(127);
		}
	}
}

int	redir_out_built(t_env *env, t_cmd cmd, int builtin, char *line)
{
	int	value;

	value = 0;
	if (builtin == 1)
		value = do_echo(cmd.cmd_args);
	else if (builtin == 2)
	{
		value = cd(env, cmd.cmd_args[1]);
		set_thepwd(env);
	}
	else if (builtin == 3)
		ft_putendl_fd(get_pwd(), 1);
	else if (builtin == 4)
	{
		close(cmd.io_in);
		exito(cmd.cmd_args[1], &cmd, env, line);
	}
	else if (builtin == 5)
		value = export_the(env, &cmd.cmd_args[1]);
	else if (builtin == 6)
		value = do_the_unset(env, cmd.cmd_args);
	else if (builtin == 7)
		value = printf_the_env(env, cmd.cmd_args);
	close(cmd.io_in);
	return (value);
}

void	built(t_env *env, t_cmd cmd, int *value, int builtin)
{
	if (builtin == 1)
		*value = do_echo(cmd.cmd_args);
	else if (builtin == 2)
	{
		*value = cd(env, cmd.cmd_args[1]);
		set_thepwd(env);
	}
	else if (builtin == 3)
		ft_putendl_fd(get_pwd(), 1);
	else if (builtin == 4)
		exito(cmd.cmd_args[1], &cmd, env, NULL);
	else if (builtin == 5)
		*value = export_the(env, &cmd.cmd_args[1]);
	else if (builtin == 6)
		*value = do_the_unset(env, cmd.cmd_args);
	else if (builtin == 7)
		*value = printf_the_env(env, cmd.cmd_args);
}

int	redir_double_built(t_env *env, t_cmd cmd, int builtin, char *line)
{
	int	fd1;
	int	value;

	value = 0;
	(void)line;
	fd1 = dup(1);
	close(1);
	dup(cmd.io_out);
	if (builtin >= 1 && builtin <= 7)
		built(env, cmd, &value, builtin);
	close(cmd.io_out);
	close(cmd.io_in);
	dup2(fd1, 1);
	return (value);
}

