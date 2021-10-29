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

int	malloc_of_pipe(t_cmd *cmd, t_pipe *pip)
{
	t_cmd *tmp;

	tmp = cmd;
	pip->i = 0;
	pip->nbr_p = nbr_of_pipe(tmp);
	pip->nbr_cmd = pip->nbr_p + 1;
	pip->pipefd = malloc(sizeof(int) * (pip->nbr_p * 2));
	if ( pip->pipefd == NULL)
	{
		perror("malloc");
		return (-1);
	}
	pip->pid = malloc(sizeof(int) * (pip->nbr_cmd));
	if (pip->pid == NULL)
	{
		free (pip->pipefd);
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
int	first_pid(t_cmd cmd, t_env *env, int *pipefd, int nbr_p, int save )
{
	int redir;
	int	fd;
	char	**tenvp;

	(void)save;
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
		exit(1);
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
	else if (redir == 3) // redir << 
	{

		fd = open(".here_doc", O_RDWR | 0666);
		dup2(fd, 0);
		if ( cmd.io_out > 0)
			dup2(cmd.io_out, 1);
		else
			dup2(pipefd[1], 1);
		close_all_p(pipefd, nbr_p);
		close(fd);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
//	else if ( redir == 4) // redir > < 
	unlink(".here_doc");
	return (0);
}

int	last_pid(t_cmd cmd, t_env *env, int *pipefd, int nbr_p)
{
	char **tenvp;
	int	redir;
	int fd;

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
		close(cmd.io_out);
		dup2(pipefd[nbr_p - 2], 0);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
		exit(1);
		}
	else if ( redir == 2) // redir <
	{
		dup2(cmd.io_in, 0);
		close(cmd.io_in);
	//	dup2(pipefd[nbr_p - 1], 1);
		close_all_p(pipefd, nbr_p);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if ( redir == 3) // redir <<
	{
		
		close_all_p(pipefd, nbr_p);
		if ( cmd.io_out > 0)
			dup2(cmd.io_out, 1);
		fd = open(".here_doc", O_RDWR, 0666);
		dup2(fd, 0);
		close(fd);
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	exit(1);
//	else if ( redir == 4) // redir > < 
	unlink (".here_doc");
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

int	other_pid(t_cmd cmd, t_env *env, t_pipe pip)
{
	char	**tenvp;
	int		redir;
	int		fd;

	redir = which_redir(cmd);
	tenvp = list_to_cmd(env);
	if (redir == 0) // pas de redir
	{
		dup2(pip.pipefd[pip.i + (pip.i  - 2)], 0);
		dup2(pip.pipefd[pip.i + (pip.i  + 1)], 1);
		close_all_p(pip.pipefd, (pip.nbr_p * 2));
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if (redir == 1) //redir >
	{
		dup2(pip.pipefd[pip.i + (pip.i  - 2)], 0);
		dup2(cmd.io_out, 1);
		close_all_p(pip.pipefd, (pip.nbr_p * 2));
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
		dup2(pip.pipefd[pip.i + (pip.i  + 1)], 1);
		close_all_p(pip.pipefd, (pip.nbr_p * 2));
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
	else if ( redir == 3) // redir << 
	{
		fd = open(".here_doc", O_RDWR , 0666);
		dup2(fd , 0);
		close(fd);
		if ( cmd.io_out > 0)
		{
			dup2(cmd.io_out , 1);
			close(cmd.io_out);
		}
		else
			dup2(pip.pipefd[pip.i + (pip.i  + 1)], 1);
		close_all_p(pip.pipefd, (pip.nbr_p * 2));
		if ( execve(cmd.cmdp, cmd.cmd_args,tenvp) == -1)
		{
			perror(cmd.cmd_args[0]);
			exit(127);
			return (-1);
		}
	}
//	else if ( redir == 4) // redir > < 
	unlink(".here_doc");
	return (0);
}

int	do_the_pipe(t_cmd *cmd, t_env *env)
{
	t_pipe	pip;

	int	save = 0;

//	save = dup(1);
	if (malloc_of_pipe(cmd, &pip) == -1)
		return (-1);
	if (deploy_pipe(pip.pipefd, pip.pid, pip.nbr_cmd, ((pip.nbr_p) * 2)) == -1)
		return (-1);
	while (cmd)
	{
			if ( cmd->dless == 1)
		pip.pid[pip.i] = fork();
		if (pip.pid[pip.i] == 0)
		{
		if (cmd->next != NULL && cmd->dless == 1 )
			{
			here_doc(env, *cmd, 0);
			}
			if (pip.i == 0)
		{
				if (first_pid(*cmd, env, pip.pipefd, ((pip.nbr_p) * 2), save) == -1)
					return (-1);
			}
			else if (pip.i == pip.nbr_cmd -1)
			{
				if (last_pid(*cmd, env, pip.pipefd, ((pip.nbr_p) * 2)) == -1)
					return (-1);
			}
			else
				if (other_pid(*cmd, env, pip) == -1)
					return (-1);
		}
		}
		if ( cmd->io_out > 0)
			close(cmd->io_out);
		if ( cmd->io_in > 0)
			close(cmd->io_in);
		
		pip.i++;
		cmd = cmd->next;
	}
	we_wait(pip.pid, pip.nbr_cmd, pip.pipefd, ((pip.nbr_p) *2));
		unlink(".here_doc");
	return (0);
}
