/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:05:27 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 18:27:28 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * permet d'articulier le parser avec mes builtin
 * echo is good
 */
/* !!!!!!!
 * need to gerer export a ca va s'afficher dans export
 * mais pas dans env
 * gerer le export btw
 * mettre export en **
 */
// fo incremeter les shlvl  de +1 au debut comme ca  cgerer
void	exec_the_built(t_env *env, t_cmd *cmd, char *line, int builtin)
{
	char	*buf;

	if (builtin == 1)
		return_value = do_echo(cmd->cmd_args);
	else if (builtin == 2)
	{
		return_value = cd(env, cmd->cmd_args[1]);
		set_thepwd(env);
	}
	else if (builtin == 3)
	{
		buf = get_pwd();
		ft_putendl_fd(buf, 1);
		free(buf);
		return_value = 0;
	}
	else if (builtin == 4)
		exito(cmd->cmd_args[1], cmd, env, line);
	else if (builtin == 5)
		return_value = export_the(env, &cmd->cmd_args[1]);
	else if (builtin == 6)
		return_value = do_the_unset(env, cmd->cmd_args);
	else if (builtin == 7)
		return_value = printf_the_env(env, cmd->cmd_args);
}

void	no_a_builtin(t_cmd *cmd, t_env *env, int status)
{
	char	**tenvp;
	pid_t	pid;

	tenvp = list_to_cmd(env);
	pid = fork();
	if (pid == 0)
		ft_execve(cmd->cmdp, cmd->cmd_args, tenvp);
	handle_signal(CHILD_HANDLING);
	waitpid(pid, &status, 0);
	set_status(status, 1);
	ft_free_double_tab(tenvp);
}

void	cmd_to_exec(t_cmd *cmd, t_env *env, char *line)
{
	int		status;
	int		builtin;

	status = 0;
	if (cmd == NULL)
		return ;
	while (cmd && cmd->index >= 0)
	{
		if (cmd->next)
		{
			if (do_the_pipe(cmd, env) == 0)
				return ;
		}
		else if (there_is_redir (env, *cmd, line) == 0)
			status = 0;
		else
		{
			builtin = is_a_builtin(cmd->cmd_args[0]);
			if (builtin >= 1 && builtin <= 7)
				exec_the_built(env, cmd, line, builtin);
			else if (builtin == 0)
				no_a_builtin(cmd, env, status);
		}
		cmd = cmd->next;
	}
}
