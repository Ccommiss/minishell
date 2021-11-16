/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:41:40 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/10 11:33:16 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(char *path, char **cmd, char **tenvp)
{
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

void	redir_out_built(t_env *env, char **cmd, int fd, int builtin)
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
		exito(cmd[1]);
	else if (builtin == 5)
		export_the(env, &cmd[1]);
	else if (builtin == 6)
		do_the_unset(env, cmd);
	else if (builtin == 7)
		printf_the_env(env);
	close(fd);
}

void	fork_fail_d(char *str, int fd, int fd1, char **tenvp)
{
	perror(str);
	close(fd);
	close(fd1);
	ft_free_double_tab(tenvp);
	return ;
}

void	no_cmd_d(int fd, int fd1)
{
	close(fd);
	close(fd1);
	return ;
}

void	redir_double_built(t_env *env, t_cmd cmd, int builtin)
{
	int	fd1;

	fd1 = dup(1);
	close(1);
	dup(cmd.io_out);
	if (builtin == 1)
		do_echo(cmd.cmd_args);
	else if (builtin == 2)
	{
		cd(env, cmd.cmd_args[1]);
		set_thepwd(env);
	}
	else if (builtin == 3)
		ft_putendl_fd(get_pwd(), 1);
	else if (builtin == 4)
		exito(cmd.cmd_args[1]);
	else if (builtin == 5)
		export_the(env, &cmd.cmd_args[1]);
	else if (builtin == 6)
		do_the_unset(env, cmd.cmd_args);
	else if (builtin == 7)
		printf_the_env(env);
	close(cmd.io_out);
	close(cmd.io_in);
	dup2(fd1, 1);
}
