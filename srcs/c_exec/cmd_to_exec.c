/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:05:27 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/22 16:01:17 by mpochard         ###   ########.fr       */
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

void	cmd_to_exec(t_cmd *cmd, t_env *env)
{

	int		status = 0;
	(void)env;
	char	*buf;
	char	**tenvp;

		if (cmd == NULL)
			return_value = 0;
	while (cmd && cmd->index >= 0)
	{
		if (cmd->error == TRUE)
		{
			cmd = cmd->next;
			break ;
		}
		if (cmd->next)
		{
			if (do_the_pipe(cmd, env) == 0)
				return ;
		}
		else if ( there_is_redir(env, *cmd) == 0)
		{

		}
		else
		{
			if (cmd->cmd_args[0] != NULL && strcmp(cmd->cmd_args[0], "echo") == 0)
				return_value = do_echo(cmd->cmd_args);
			else if (cmd->cmd_args[0] != NULL &&strcmp(cmd->cmd_args[0], "cd") == 0)
			{
				return_value =cd(env, cmd->cmd_args[1]);
				set_thepwd(env);
			}
			else if (cmd->cmd_args[0] != NULL && strcmp(cmd->cmd_args[0], "pwd") == 0)
			{
				buf = get_pwd();
				ft_putendl_fd(buf, 1);
				free(buf);
				return_value = 0;
			}
			else if(cmd->cmd_args[0] && strcmp(cmd->cmd_args[0], "env") == 0)
				return_value =printf_the_env(env, cmd->cmd_args);
			else if(cmd->cmd_args[0] && strcmp(cmd->cmd_args[0], "export") == 0)
			{
				return_value =export_the(env, &cmd->cmd_args[1]);
			}
			else if(cmd->cmd_args[0] != NULL && ft_strncmp(cmd->cmd_args[0], "exit", 5) == 0)
					exito(cmd->cmd_args[1]);
			else if (cmd->cmd_args[0] && strcmp(cmd->cmd_args[0], "unset") == 0)
				return_value = do_the_unset(env, cmd->cmd_args);
			else
			{
				pid_t pid;
				tenvp = list_to_cmd(env);
				pid = fork();
				if (pid == 0)
				{
					handle_signal(CHILD);
					if (execve(cmd->cmdp, cmd->cmd_args,tenvp) == -1)
					{
						printf ("minishell: command not found: %s\n", cmd->cmd_args[0]);
						exit (127);
					}
				}
				else
					handle_signal(CHILD_HANDLING);
				waitpid(pid, &status, 0);
				set_status(status);
			}
		}
		cmd = cmd->next;
	}
}
