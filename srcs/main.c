/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:46:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/10/21 17:31:04 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>




int	check_quote(char *line)
{
	int	i;
	int check;

	i = 0;
	while (line[i])
	{
		check = 0;
		if (line[i] == '\'')
		{
			check = 1;
			i++;
			while (line[i]  && line[i] != '\'')
				i++;
			if (line[i] && line[i] == '\'')
				check = 2; 
		}
		if (line[i] == '\"')
		{
			check = 1;
			i++;
			while (line[i]  && line[i] != '\"')
				i++;
			if (line[i] && line[i] == '\"')
				check = 2;
		}
		i++;

	}
		if (check == 1)
			return (-1);
	return (0);
}

void	start_cmd(t_cmd *cmd)
{
	cmd->cmd_args = NULL;
	cmd->cmdp = NULL;
	cmd->index = -1;
	cmd->prev = NULL;
	cmd->io_in = NOT_SPECIFIED;
	cmd->io_out = NOT_SPECIFIED;
	cmd->dgreat = FALSE;
	cmd->dless = FALSE;
}


int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token toks;
	t_cmd	cmd;

	(void)ac;
	(void)av;
	t_env *env;



	env = NULL;
	get_the_env(&env, envp);

	while (1)
	{
		handle_signal(MAIN_PROCESS);
		line = readline(BWHT"> "RESET);
		
		if (line && ft_strlen(line) > 0)
		{
			//printf ("main %d %d \n", getpid(), getppid());
			add_history(line);
			init_token(&toks);
			start_cmd(&cmd);
			tokenize(line, &toks, env);
			debug_tokens(&toks);
			token_to_cmds(&cmd, &toks);
			find_path(&cmd, env);
			debug_cmds(&cmd);
			cmd_to_exec(&cmd,env);
		}
		else if (!line)
			exit(0);

	//free(line);
	}
	
	return (0);
}
