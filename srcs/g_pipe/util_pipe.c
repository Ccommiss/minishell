/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:36:27 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/16 13:35:57 by mpochard         ###   ########.fr       */
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

int	malloc_of_pipe(t_cmd *cmd, int **pipefd, pid_t **pid, int *nbr_cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	*nbr_cmd = nbr_of_pipe(tmp) + 1;
	*pipefd = malloc(sizeof(int) * ((*nbr_cmd - 1) * 2));
	if (*pipefd == NULL)
	{
		perror("malloc");
		return (-1);
	}
	*pid = malloc(sizeof(int) * (*nbr_cmd));
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
	int	i;

	i = 0;
	(void)nbr_cmd;
	while (i < nbr_p)
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

void	we_wait(pid_t *pid, int nbr_cmd, int *pipefd, int pipee)
{
	int	i;
	int	status;

	i = 0;
	close_all_p(pipefd, pipee);
	while (i < nbr_cmd)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	set_status(status);
	free(pid);
	free(pipefd);
}
