#include "minishell.h"
#include <fcntl.h>
void	simple_redir_o(t_env *env, int fd, char **cmd)
{
	pid_t pid;
	int builtin;

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
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		dup2(fd, 0);
		if (execvp(cmd[0], cmd) == -1)
			perror(">");
	}
	waitpid(pid, NULL, 0);
	close(fd);
	}
}

void	both_redir(t_env *env, char **cmd, int in, int out)
{
	int builtin;
	pid_t pid;

	builtin = is_a_builtin(cmd[0]);
	if (builtin == 2 && in > -1 && out > -1)
	{
			if ( builtin == 2)
	{
			cd(env, cmd[1]);
			set_thepwd(env);
			return ;
	}
	}
	else if ( in > -1 && out > -1)
	{
		pid = fork();
		if (pid == 0)
		{
		dup2(out, 1);
		dup2(in, 0);
		if (builtin == 0)
		{
			execvp(cmd[0], cmd);
			perror(">");
		}
			else if (builtin == 1)
		{
			do_echo(cmd);
			exit(1);
		}
		else if (builtin == 3)
		{
			write(1,get_pwd(), ft_strlen(get_pwd()));
			write(1, "\n", 1);
			exit(1);
		}
		waitpid(pid, NULL, 0);
		close(in);
		close(out);
		}
	}
}
