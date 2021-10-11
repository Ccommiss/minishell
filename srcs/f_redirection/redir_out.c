#include "../../include/minishell.h"

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
			cd(env, NULL, 0);
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
	pid = fork;
	if (fork == -1)
	{
		perro("fork");
		return ;
	}
	if (pid == 0)
	{

		dup2(fd, 0);
		execvp(cmd[0], cmd);
	}
	waitpid(pid, NULL, 0);
	close(fd);
}

void	
