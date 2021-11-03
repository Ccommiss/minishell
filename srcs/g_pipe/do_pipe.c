#include "minishell.h"

int	nbr_of_pipe(t_cmd *cmd)
{
	int nbr;

	nbr = 0;
	while (cmd->next)
	{
		nbr++;
	cmd = cmd->next;
	}
	return (nbr);
}	

int	malloc_of_pipe(t_cmd *cmd, int **pipefd, pid_t **pid, int *nbr_cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	*nbr_cmd = nbr_of_pipe(tmp) + 1;
	*pipefd = malloc(sizeof(int) * ((*nbr_cmd -1) * 2));
	if ( *pipefd == NULL)
	{
		perror("malloc");
		return (-1);
	}
	*pid = malloc(sizeof(int) * ( *nbr_cmd));
	if (pid == NULL)
	{
		free (pipefd);
		perror("malloc");
		return (-1);
	}
	return (0);
}

void	close_all_p(int *fd, int nbr)
{
	int	x;

	x = 0;
	while (x < nbr)
	{
		close(fd[x]);
		x++;
	}
}

int	deploy_pipe(int *pipefd, pid_t *pid, int nbr_cmd, int nbr_p)
{
	int i;

	i = 0;
	(void)nbr_cmd;
	while ( i < nbr_p)
	{
		if (pipe(pipefd + i) < 0)
		{
			free(pipefd);
			free(pid);
			return (-1);
		}
		i += 2;
	}
	return (0);
}

int	which_redir(t_cmd cmd)
{
	if ( cmd.dless == 1)
		return (3);
	else if (cmd.io_out > 1 && cmd.io_in < 0)
		return (1);
	else if ( cmd.io_in > 1 && cmd.io_out < 0)
		return (2);
	else if (cmd.io_in > 1 && cmd.io_out > 0)
		return (4);
	return (0);
}
int	first_pid(t_cmd cmd, t_env *env, int *pipefd, int nbr_p )
{
	int redir;
	char	**tenvp;

	redir = which_redir(cmd);
	tenvp = list_to_cmd(env);
	if (redir == 0) // aucune redir
	{
		dup2(pipefd[1], 1);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if (redir == 1)// redir >
	{
		dup2(cmd.io_out, 1);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if (redir == 2) // redir <
	{
		dup2(cmd.io_in, 0);
		dup2(pipefd[1], 1);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if ( redir == 4) // redir > < 
	{
		dup2(cmd.io_in, 0);
		dup2(cmd.io_out, 1);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	return (0);
}

int	last_pid(t_cmd cmd, t_env *env, int *pipefd, int nbr_p)
{
	char **tenvp;
	int	redir;

	tenvp = list_to_cmd(env);
	redir = which_redir(cmd);
	if (redir == 0) // no redir
	{
		dup2(pipefd[nbr_p - 2], 0);
		close_all_p(pipefd, nbr_p);
		if (execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if ( redir == 1) // redir >
	{
		dup2(cmd.io_out, 1);
		dup2(pipefd[nbr_p - 2], 0);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if ( redir == 2) // redir <
	{
		dup2(cmd.io_in, 0);
		dup2(pipefd[nbr_p - 1], 1);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if ( redir == 4) // redir > < 
	{
		dup2(cmd.io_in, 0);
		dup2(cmd.io_out, 1);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	return (0);
}

int	other_pid(t_cmd cmd, t_env * env,int *pipefd, int i, int nbr_p)
{
	char	**tenvp;
	int		redir;

	redir = which_redir(cmd);
	tenvp = list_to_cmd(env);
	if ( redir == 0) // no redir
	{
		dup2(pipefd[i + (i - 2)], 0);
		dup2(pipefd[i + i + 1], 1);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if ( redir == 1) //redir > 
	{
		dup2(pipefd[i + (i - 2)], 0);
		dup2(cmd.io_out ,1);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if ( redir == 2)// redir < 
	{
		dup2(pipefd[i + i + 1], 1);
		dup2(cmd.io_in ,0);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if ( redir == 4) // redir > < 
	{
		dup2(cmd.io_in, 0);
		dup2(cmd.io_out, 1);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	return (0);
}

void	we_wait(pid_t *pid, int nbr_cmd ,int *pipefd, int pipee)
{
	int	i;

	i = 0;
	close_all_p(pipefd, pipee);
	while (i < nbr_cmd)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
	free(pipefd);
}

int	do_the_pipe(t_cmd *cmd, t_env *env)
{
	int		nbr_cmd;
	int		*pipefd;
	pid_t		*pid;
	int			i;

	i = 0;
	if (malloc_of_pipe(cmd, &pipefd, &pid, &nbr_cmd) == -1)
		return (-1);
	if (deploy_pipe(pipefd, pid, nbr_cmd, ((nbr_cmd - 1) * 2)) == -1)
		return (-1);
	while (i < nbr_cmd)
	{
		if (cmd->dless == 1)
			fill_thefd(*cmd);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (cmd->dless == 1)
			{
				if ( cmd->io_out < 0 && i == 0)
					dup2(pipefd[1], 1);
				else if ( cmd->io_out && i < nbr_cmd - 1)
					dup2(pipefd[i + i + 1], 1);
				here_doc( env, *cmd, 0);
				close_all_p(pipefd, (nbr_cmd - 1) * 2);
				exit(1);
			}
			else if (i == 0)
			{
				if (first_pid(*cmd, env, pipefd, ((nbr_cmd - 1) * 2)) == -1)
					return (-1);
			}
			else if (i == nbr_cmd -1)
			{
				if (last_pid(*cmd, env, pipefd, ((nbr_cmd - 1) * 2)) == -1)
					return (-1);
			}
			else
			{
				if (other_pid(*cmd, env, pipefd, i, (nbr_cmd - 1) * 2 ) == -1)
					return (-1);
			}
	}
			if ( cmd->dless == 1)
				waitpid(pid[i], NULL, 0);
			if ( cmd->io_out > 0)
				close(cmd->io_out);
			if ( cmd->io_in > 0)
				close(cmd->io_in);
		i++;
		cmd = cmd->next;
	}
	we_wait(pid, nbr_cmd, pipefd, ((nbr_cmd -1) *2));
	unlink(".here_doc");
	return (0);
}
