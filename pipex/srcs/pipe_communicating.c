/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_communicating.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 15:51:34 by ccommiss          #+#    #+#             */
/*   Updated: 2021/07/22 15:51:34 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	Redirects stdin on read ends of fds, or infile if first command
**	Redirects stdout on write ends of fds, or outfile if last command
*/
void	dup_and_exec(t_cmd *cmds, int *files, int **fd, char **envp)
{
	if (cmds && cmds->index == 0)
		if (dup2(files[INFILE], STDIN_FILENO) == -1)
			error_quit(DUP_ERR, cmds->head, fd);
	if (cmds && cmds->index != 0)
	{
		if (dup2(fd[cmds->index - 1][0], STDIN_FILENO) < 0)
			error_quit(DUP_ERR, cmds->head, fd);
		close(fd[cmds->index - 1][1]);
		close(fd[cmds->index - 1][0]);
	}
	if (cmds && cmds->next == NULL)
		if (dup2(files[OUTFILE], STDOUT_FILENO) == -1)
			error_quit(DUP_ERR, cmds->head, fd);
	if (cmds && cmds->next != NULL)
	{
		close(fd[cmds->index][0]);
		if (dup2(fd[cmds->index][1], STDOUT_FILENO) == -1)
			error_quit(DUP_ERR, cmds->head, fd);
		close(fd[cmds->index][1]);
	}
	if (execve(cmds->cmdp, cmds->cmd_args, envp) == -1)
		error_quit(EXEC_ERR, cmds->head, fd);
}

/*
**	Parent is closing fds
*/
void	close_fds(int **fd, t_cmd *cmds)
{
	close(fd[cmds->index - 1][1]);
	close(fd[cmds->index - 1][0]);
}

void	free_fds(int **fd, t_cmd *head)
{
	int		pipes;
	t_cmd	*tmp;

	pipes = 0;
	while (head != NULL)
	{
		tmp = head;
		free(head->cmdp);
		ft_free_double_tab(head->cmd_args);
		head = head->next;
		if (tmp->index > pipes)
			pipes = tmp->index;
		free(tmp);
	}
	while (pipes-- > 0)
		free(fd[pipes]);
	free(fd);
	fd = NULL;
}

/*
**		> Creation double tab to handle X pipe of
**		int[2]
**
**     fd[0][0/1]       fd[2][0/1]
**        v                 v
**	cmd1  |  cmd2  |  cmd3  |  cmd4  |  cmd5
**             	   ^                 ^
**          	fd[1][0/1]             fd[3][0/1]
*/
int	main(int ac, char **argv, char **envp)
{
	int		files[2];
	int		**fd;
	pid_t	pid;
	t_cmd	*cmds;
	t_cmd	*head;

	get_file(files, argv, ac);
	pipe_fds(&fd, ac - 4);
	cmds = take_multiple_args(argv, ac, envp);
	head = cmds;
	while (cmds != NULL)
	{
		pid = fork();
		if (pid == -1)
			error_quit(FORK_ERR, cmds->head, fd);
		if (pid == 0)
			dup_and_exec(cmds, files, fd, envp);
		if (cmds->index >= 1)
			close_fds(fd, cmds);
		cmds = cmds->next;
	}
	free_fds(fd, head);
	return (0);
}
