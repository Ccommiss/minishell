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
	int	i;
	char	*line;

	i = 0;
	while (cmd.here_words)
	{
//		unlink(".here_doc");
		fd = open(".here_doc", O_CREAT | O_TRUNC | O_RDWR , 0777);
		if ( fd == -1)
		{
			perror(">");
			return (-1);
		}
		while (1)

		{
			line = readline(">");
			if ( line )
			{
			if (ft_strncmp(cmd.io_here[i], line, ft_strlen(cmd.io_here[i])) == 0)
			{
				free(line);
				break;
			}
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		i++;
		cmd.here_words--;
		close(fd);
	}
/*	fd = open (".here_doc", O_RDWR);
	char buf[42];
	int ret = read(fd, buf , 42);
	buf[42] = '\0';
	printf ("ret = %d\n[", ret);
	for (int j = 0; j <42; j++)
		printf("%c", buf[j]);
	printf("]\n");
	close(fd);*/
	return (fd);
}


void	here_doc(t_env *env, t_cmd cmd, int fd)
{
	int		builtin;
	pid_t	pid;
	pid_t	pid1;
	int		fd1;
	char	**tenvp;

	(void)fd;
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if (builtin == 2)
	{
		cd(env, cmd.cmd_args[1]);
		set_thepwd(env);
	}
	else if ( builtin == 1 ||  builtin > 2)
	{
		pid1 = fork();
		if ( pid1 == 0)
		{
			if ( cmd.io_out > 1)
				dup2(cmd.io_out, 1);
			if (builtin == 1)
				do_echo(cmd.cmd_args);
			else if (builtin == 3)
			{
				write(1, get_pwd(), ft_strlen(get_pwd()));
				write(1, "\n",1);
			}
			unlink(".here_doc");
			exit(1);
		}
		return ;
	}
	else
	{
		tenvp = list_to_cmd(env);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return ;
		}
		else if (pid == 0)
		{
			fd1 = open(".here_doc", O_RDWR, 0666);
			if ( cmd.io_out > 1)
				dup2(cmd.io_out, 1);
			dup2(fd1, 0);
			if (execve(cmd.cmdp, cmd.cmd_args, tenvp) == -1)
			{
				perror(cmd.cmd_args[0]);
				unlink (".here_doc");
				exit(1);
			}
		}
		waitpid(pid, NULL, 0);
		//	}
}
unlink (".here_doc");
}
