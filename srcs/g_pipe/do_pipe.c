/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:25 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/08 15:00:17 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_redir(t_cmd cmd)
{
	if (cmd.dless == 1)
		return (3);
	else if (cmd.io_out > 1 && cmd.io_in < 0)
		return (1);
	else if (cmd.io_in > 1 && cmd.io_out < 0)
		return (2);
	else if (cmd.io_in > 1 && cmd.io_out > 0)
		return (4);
	return (0);
}

int	do_the_pipe(t_cmd *cmd, t_env *env)
{
	int		nbr_cmd;
	int		*pipefd;
	pid_t	*pid;
	int		i;

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
				if (cmd->io_out < 0 && i == 0)
					dup2(pipefd[1], 1);
				else if (cmd->io_out && i < nbr_cmd - 1)
					dup2(pipefd[i + i + 1], 1);
				here_doc(env, *cmd, 0);
				close_all_p(pipefd, (nbr_cmd - 1) * 2);
				exit(1);
			}
			else if (i == 0)
			{
				if (first_pid(*cmd, env, pipefd, ((nbr_cmd - 1) * 2)) == -1)
					return (-1);
			}
			else if (i == nbr_cmd - 1)
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
		if (cmd->dless == 1)
			waitpid(pid[i], NULL, 0);
		if (cmd->io_out > 0)
			close(cmd->io_out);
		if (cmd->io_in > 0)
			close(cmd->io_in);
		i++;
		cmd = cmd->next;
	}
	we_wait(pid, nbr_cmd, pipefd, ((nbr_cmd - 1) * 2));
	unlink(".here_doc");
	return (0);
}
