/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:46:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/01 15:32:14 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int return_value;

int check_quote(char *line)
{
	int i;
	int j;
	int context;

	i = 0;
	j = ft_strlen(line);
	context = WORD;
	while (line[i])
	{
		if (context == WORD && line[i] == SQUOTE)
			context = SQUOTE;
		else if (context == WORD && line[i] == DQUOTE)
			context = DQUOTE;
		else if (context == SQUOTE && line[i] == SQUOTE)
			context = WORD;
		else if (context == DQUOTE && line[i] == DQUOTE)
			context = WORD;
		i++;
	}
	if (context != WORD)
	{
		printf ("Please check quotes and close them.\n");
		free (line);
		return_value = 1;
		return (ERROR);
	}
	return (0);
}



char *choose_prompt()
{
	char *line;

	if ((!isatty(STDIN_FILENO)))
	{
		rl_outstream = stdin;
		line = readline("");
		return (line);
	}
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
			if (check_quote(line) == 0)
			{
				init_tok_and_cmd(&toks, &cmd);
				tokenize(line, &toks, env);
				debug_tokens(&toks);
				token_to_cmds(&cmd, &toks);
				find_path(&cmd, env);
				debug_cmds(&cmd);
				cmd_to_exec(&cmd, env, line);
				cleanup(&cmd, &toks, line);
			}
		}
		else if (!line)
		{
			printf("\n");
			if (isatty(STDIN_FILENO))
				exit(1);
			if (!isatty(STDIN_FILENO))
				exit(0);
		}
	}
	return (0);
}
