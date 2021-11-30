/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:36:27 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 18:39:08 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_of_pipe(t_cmd *cmd)
{
	int	nbr;

	nbr = 0;
	while (cmd->next)
	{
		nbr++;
		cmd = cmd->next;
	}
	return (nbr);
}

int	malloc_of_pipe(t_cmd *cmd, t_pipe *piped)
{
	t_cmd	*tmp;

	tmp = cmd;
	piped->nbr_cmd = nbr_of_pipe(tmp) + 1;
	piped->nbr_p = (piped->nbr_cmd - 1) * 2;
	piped->pipefd = malloc(sizeof(int) * piped->nbr_p);
	if (piped->pipefd == NULL)
	{
		perror("malloc");
		return (-1);
	}
	piped->pid = malloc(sizeof(int) * (piped->nbr_cmd));
	if (piped->pid == NULL)
	{
		free (piped->pipefd);
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

int	deploy_pipe(t_pipe piped)
{
	int	i;

	i = 0;
	while (i < piped.nbr_p)
	{
		if (pipe(piped.pipefd + i) < 0)
		{
			free(piped.pipefd);
			free(piped.pid);
			return (-1);
		}
		i += 2;
	}
	return (0);
}

void	we_wait(pid_t *pid, int nbr_cmd, int *pipefd, int pipee)
{
	int	i;
	int	status;

	i = 0;
	close_all_p(pipefd, pipee);
	while (i < nbr_cmd)
	{
		waitpid(pid[i], &status, 0);
		set_status(status, 0);
		i++;
	}
	free(pid);
	free(pipefd);
}
