/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:25 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/01 14:16:59 by mpochard         ###   ########.fr       */
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

void	if_here_doc(t_env *env, t_cmd *cmd, t_pipe piped)
{	
	if (cmd->io_out < 0 && piped.i == 0)
	{
		if (dup2(piped.pipefd[1], 1) == -1)
			perror("dup2 failed");
	}
	else if (cmd->io_out && piped.i < piped.nbr_cmd - 1)
	{
		if (dup2(piped.pipefd[piped.i + piped.i + 1], 1) == -1)
			perror("dup2 failed");
	}
	here_doc(env, *cmd, 0);
	close_all_p(piped.pipefd, piped.nbr_p);
	exit(return_value);
}

void	inside_pid(t_env *env, t_cmd *cmd, t_pipe piped)
{
	if (cmd->dless == 1)
		if_here_doc(env, cmd, piped);
	else if (piped.i == 0)
		first_pid(*cmd, env, piped.pipefd, piped.nbr_p);
	else if (piped.i == piped.nbr_cmd - 1)
		last_pid(*cmd, env, piped.pipefd, piped.nbr_p);
	else
		other_pid(*cmd, env, piped, piped.i);
}

void	after_the_pid(t_cmd *cmd, t_pipe *piped)
{
	if (cmd->dless == 1)
	{
		waitpid(piped->pid[piped->i], &piped->temp, 0);
		set_status(piped->temp, 1);
		piped->temp = return_value;
		if (piped->i == (piped->nbr_cmd - 1))
			piped->status = 1;
	}
	if (cmd->io_out > 0)
		close(cmd->io_out);
	if (cmd->io_in > 0)
		close(cmd->io_in);
}

int	do_the_pipe(t_cmd *cmd, t_env *env)
{
	t_pipe	piped;

	bzero(&piped, sizeof(t_pipe));
	if (malloc_of_pipe(cmd, &piped) == -1)
		return (-1);
	if (deploy_pipe(piped) == -1)
		return (-1);
	while (cmd)
	{
		if (cmd->dless == 1)
			fill_thefd(*cmd);
		piped.pid[piped.i] = fork();
		if (piped.pid[piped.i] == 0)
			inside_pid(env, cmd, piped);
		else
			handle_signal(CHILD_HANDLING);
		after_the_pid(cmd, &piped);
		piped.i++;
		cmd = cmd->next;
	}
	we_wait(piped.pid, piped.nbr_cmd, piped.pipefd, piped.nbr_p);
	if (piped.status == 1)
		return_value = piped.temp;
	unlink(".here_doc");
	return (0);
}
