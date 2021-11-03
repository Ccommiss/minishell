#include "minishell.h"
#include <fcntl.h>
void	simple_redir_o(t_env *env, int fd, char **cmd, char *path)
{
	pid_t pid;
	int builtin;
	char	**tenvp;
	
	if (cmd[0] == NULL)
	{
		close(fd);
		return ;
	}
	builtin = is_a_builtin(cmd[0]);
	if ((builtin >= 1 && builtin <= 4) && fd > -1)
	{
		if ( builtin == 1)
			do_echo(cmd);
		else if (builtin == 2)
		{
			cd(env, cmd[1]);
			set_thepwd(env);
		}
		else if (builtin == 3)
		{
			write(1, get_pwd(), ft_strlen(get_pwd()));
			write(1, "\n",1);
		}
		return ;
	}
	else if ( builtin == 0 && fd > -1)
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
		dup2(fd, 0);
		if (execve(path, cmd, tenvp) == -1)
		{
			perror(cmd[0]);
			exit(1);
		}
	}
	waitpid(pid, NULL, 0);
	close(fd);
	}
}

void	both_redir(t_env *env, t_cmd cmd, int in, int out)
{
	int builtin;
	pid_t pid;
	char	**tenvp;

	if ( cmd.cmd_args[0] ==  NULL)
	{
		close(in);
		close(out);
		return ;
	}
	builtin = is_a_builtin(cmd.cmd_args[0]);
	if (builtin == 2 && in >= -1 && out >= -1)
	{
			if ( builtin == 2)
			{
			cd(env, cmd.cmd_args[1]);
			set_thepwd(env);
			return ;
			}
	}
	else if ( in >= -1 && out >= -1)
	{
		tenvp = list_to_cmd(env);
		pid = fork();
		if (pid == 0)
		{
			dup2(out, 1);
			dup2(in, 0);
		if (builtin == 1)
		{
			do_echo(cmd.cmd_args);
			exit(1);
		}
		else if (builtin == 3)
		{
			write(1,get_pwd(), ft_strlen(get_pwd()));
			write(1, "\n", 1);
			exit(1);
		}
		else if (builtin == 0)
		{
			close(out);
			close(in);
			if (execve(cmd.cmdp, cmd.cmd_args, tenvp) == -1)
			{
				perror(">");
				close(in);
				close(out);
				exit(1);
			}
		}
		}
		close(out);
		close(in);
		waitpid(pid, NULL, 0);
	}
}
