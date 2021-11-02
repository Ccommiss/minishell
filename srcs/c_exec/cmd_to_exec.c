/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:05:27 by mpochard          #+#    #+#             */
/*   Updated: 2021/10/18 15:43:46 by mpochard         ###   ########.fr       */
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


void	cmd_to_exec(t_cmd *cmd, t_env *env)
{

	int status = 0;
	(void)env;
	char *buf;
/*	while ( cmd->cmd_args[i])
	{
	
		printf("cmd is %s\n", cmd->cmd_args[i]);
	i++;
	}*/
	while (cmd)
	{
		if (cmd->next)
		{
			printf ("AYA YA UN PIPE\n");
		}
		else if ( there_is_redir(env, *cmd) == 0)
		{
			
		}
		else 
		{
			
			if (strcmp(cmd->cmd_args[0], "echo") == 0)
				do_echo(cmd->cmd_args);
			else if (strcmp(cmd->cmd_args[0], "cd") == 0)
			{
				cd(env, cmd->cmd_args[1]);
				set_thepwd(env);
			}
			else if (strcmp(cmd->cmd_args[0], "pwd") == 0)
			{
				buf = get_pwd();
				ft_putendl_fd(buf, 1);
				free(buf);
			}
			else if(strcmp(cmd->cmd_args[0], "env") == 0)
				printf_the_env(env);
			else if(strcmp(cmd->cmd_args[0], "export") == 0)
			{
				if (remplace_the_var(env, cmd->cmd_args[1]) == 0)
					export_the_var(env, cmd->cmd_args[1]);
			}
			else if (strcmp(cmd->cmd_args[0], "unset") == 0)
				do_the_unset(env, cmd->cmd_args);
			else 
			{
				pid_t pid;

				pid = fork();
				if (pid == 0)
				{
					handle_signal(CHILD);
					if (execvp(cmd->cmd_args[0], cmd->cmd_args) == -1)
					{
						perror("> exec error");
						exit (127);	
					}
					
				}
				else
					handle_signal(CHILD_HANDLING);
				waitpid(pid, &status, 0);
				printf ("errno : %d %s \n", errno, strerror(errno));
				printf ("brut status = %d \n", status);
				if (errno == 2 &&	status == 2)
				{
					printf ("ici \n");
					status = 130;
				}
				debug_status(status);
				printf ("RET_VALUE = %d \n", return_value);
				errno = 0;
			}
		}
		cmd = cmd->next;
	}
}
