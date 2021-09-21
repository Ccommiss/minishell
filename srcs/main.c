/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:46:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/21 13:43:31 by mpochard         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
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
	free(line);
	}
	return (0);
}
