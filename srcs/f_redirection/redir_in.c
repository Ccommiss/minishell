#include "minishell.h"
#include <fcntl.h>

int	is_a_builtin(char *cmd)
{
	if (strcmp(cmd, "echo") == 0)
		return (1);
	if (strcmp(cmd, "cd") == 0)
		return (2);
	if (strcmp(cmd, "pwd") == 0)
		return (3);
	if (strcmp(cmd, "exit") == 0)
		return (4);
	return (0);
}
void	redir_in(t_env *env, char **cmd, int fd, char *path)
{
	pid_t pid;
	int	builtin;
	char	**tenvp;

	if ( cmd[0] == NULL)
	{
		close(fd);
		return ;
	}
	builtin = is_a_builtin(cmd[0]);
	if ( builtin == 2)
	{
			cd(env, cmd[1]);
			set_thepwd(env);
			return ;
	}
	tenvp = list_to_cmd(env);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if ( pid == 0)
	{
		dup2(fd, 1);
		if (builtin == 0)
		{
			if (execve(path, cmd, tenvp) == -1)
			{
				perror(cmd[0]);
				exit(1);
			}
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
	}
		waitpid(pid, NULL, 0);
		close(fd);
}



