/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:46:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/28 15:39:49 by ccommiss         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token *toks;

	(void)ac;
	(void)av;
	t_env *env;

	env = NULL;
	get_the_env(&env, envp);
	while (1)
	{
		line = readline(BWHT"> "RESET);
		if (line)
			add_history(line);
		if (check_quote(line) ==-1)
		{
			free(line);
			printf("quote are not closed\n");
			continue;
		}
		if ( strcmp(line, "env") == 0) // test for the cmd env
			printf_the_env(env);
		//if (strcmp(line, "export") == 0)
		//	export_the_var(&env,"ls=qw");

		if (line)
		{
			toks = malloc(sizeof(t_token));
			init_token(toks);
			tokenize(line, toks, env);
			debug_tokens(toks);
			free(toks);
			toks = NULL;
		}

	free(line);
	}
	return (0);
}
