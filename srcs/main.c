/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:46:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/24 18:50:05 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
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

	(void)ac;
	(void)av;
	t_env *env;

	env = NULL;
	get_the_env(&env, envp);
	while (1)
	{
		line = readline("> ");
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
		if (strcmp(line, "export") == 0)
			export_the_var(&env,"ls=qw");
	free(line);
	}
	return (0);
}
