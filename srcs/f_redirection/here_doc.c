/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:11:36 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/16 15:00:24 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int fill_thefd(t_cmd cmd)
{
	int fd;
	int i;
	char *line;

	i = 0;
	g_utils.g_sig = 0;
	handle_signal(HEREDOC);
	while (cmd.here_words && g_utils.g_sig == 0)
	{
		fd = open(".here_doc", O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (fd == -1)
		{
			perror(">");
			return (-1);
		}
		while (g_utils.g_sig == 0)
		{
			printf("sig = %d \n\n", g_utils.g_sig);
			line = readline("> ");
			printf ("[line] : %s \n", line);
			if (line && g_utils.g_sig == 0)
			{
				if (ft_strncmp(cmd.io_here[i], line, ft_strlen(cmd.io_here[i])) == 0)
				{
					free(line);
					break;
				}

			}
				else if (line == NULL)
				{
					free (line);
					break;
				}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		i++;
		cmd.here_words--;
		close(fd);
	}
	return (fd);
}
void no_cmd_here(int in, int out)
{
	if (in > 0)
		close(in);
	if (out > 0)
		close(out);
	unlink(".here_doc");
	return;
}

void here_doc(t_env *env, t_cmd cmd, int fd)
{
	(void)env;
	(void)cmd;
	(void)fd;
	/*	int		builtin;
	pid_t	pid;
	char	**tenvp;

	if ( cmd.cmd_args[0] == NULL)
		return (no_cmd_here(cmd.io_in, cmd.io_out));
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if ((builtin >= 1 && builtin <= 7))

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
	}*/
	/*	else if (builtin == 0)
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
			fd = open(".here_doc", O_RDWR, 0666);
			if ( cmd.io_out > 1)
				dup2(cmd.io_out, 1);
			dup2(fd, 0);
			ft_execve(cmd.cmdp, cmd.cmd_args, tenvp);
		}
		waitpid(pid, NULL, 0);
		}
unlink (".here_doc");*/
}
