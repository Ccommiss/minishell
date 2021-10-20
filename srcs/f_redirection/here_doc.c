/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:11:36 by mpochard          #+#    #+#             */
/*   Updated: 2021/10/20 12:25:35 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_thefd(t_cmd cmd)
{
	int fd;
	char	*line;

	fd = open(".here_doc", O_CREAT | O_RDWR , 0777);
	if ( fd == -1)
	{
		perror(">");
		return (-1);
	}
	while (1)
	{
		line = readline(">");
		if (ft_strncmp(*cmd.io_here, line, ft_strlen(*cmd.io_here)) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		}
	close(fd);
	return (fd);
}


void	here_doc(t_env *env, t_cmd cmd, int fd)
{
	int		builtin;
	pid_t	pid;
	int		fd1;

	(void)env;
	(void)fd;
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if ( cmd.io_out > 1)
			dup2(cmd.io_out, 1);
	if ( builtin >= 1 && builtin <= 4)
	{
		if ( builtin == 1)
			do_echo(cmd.cmd_args);
		else if (builtin == 2)
		{
			cd(env, cmd.cmd_args[1]);
			set_thepwd(env);
		}
		else if (builtin == 3)
		{
			write(1, get_pwd(), ft_strlen(get_pwd()));
			write(1, "\n",1);
		}
		unlink(".here_doc");
		return ;
	}
	else
	{
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
	//
	fd1 = open(".here_doc", O_RDWR, 0666);
		dup2(fd1, 0);
		if (execvp(cmd.cmd_args[0], cmd.cmd_args) == -1)
			perror(">");
	}
	waitpid(pid, NULL, 0);
//	}
	unlink (".here_doc");
	}
}
