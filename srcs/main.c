/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:46:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/19 13:34:09 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

//t_utils g_utils;
int return_value;

int check_quote(char *line)
{
	int i;
	int check;

	i = 0;
	while (line[i])
	{
		check = 0;
		if (line[i] == '\'')
		{
			check = 1;
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] && line[i] == '\'')
				check = 2;
		}
		if (line[i] == '\"')
		{
			check = 1;
			i++;
			while (line[i] && line[i] != '\"')
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



char *choose_prompt()
{
	char *line;

	if (return_value != 0)
		line = readline(BWHT "Minishell " BRED "> " RESET);
	else
		line = readline(BWHT "Minishell " BGRN "> " RESET);
	return (line);
}

int main(int ac, char **av, char **envp)
{
	char *line;
	t_token toks;
	t_cmd cmd;
	t_env *env;

	env = NULL;
	(void)ac;
	(void)av;
	if (envp[0] == NULL)
		return (printf(" need environment\n"));
	get_the_env(&env, envp);
	while (1)
	{
		handle_signal(MAIN_PROCESS);
		line = choose_prompt();
		if (line && ft_strlen(line) == 0)
			return_value = 0;
		if (line && ft_strlen(line) > 0)
		{
			add_history(line);
			init_tok_and_cmd(&toks, &cmd);
			tokenize(line, &toks, env);
			debug_tokens(&toks);
			token_to_cmds(&cmd, &toks);
			find_path(&cmd, env);
			debug_cmds(&cmd);
			cmd_to_exec(&cmd, env);
			cleanup(&cmd, &toks, line);
		}
		else if (!line)
			exit (1);
	}
	return (0);
}
