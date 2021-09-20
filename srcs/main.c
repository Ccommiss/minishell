/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:46:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/20 10:45:34 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	init_check_op(int *i, int *count, int *count1, int *pipe)
{
	int	nb_redir;

	nb_redir = 0;
	*i = 0;
	*count = 0;
	*count1 = 0;
	*pipe = 0;
	return (nb_redir);
}

int	check_op(char *line, t_arg *op)
{
	int	i;
	int	count;
	int	count1;
	int	pipe;
	int	nb_redir;

	nb_redir = init_check_op(&i, &count, &count1, &pipe);
	while (line[i])
	{
		if (line[i] == '\'')
			count++;
		if (line[i] == '\"')
			count1++;
		if (line[i] == '|')
			pipe++;
		if (line[i] == '<' || line[i] == '>')
			nb_redir++;
		i++;
	}
	if (count % 2 == 1 || count1 % 2 == 1)
		return (printf("quote are not closed\n"));
	op->d_quote = count1;
	op->s_quote = count;
	op->nb_pipe = pipe;
	return (0);
}
/* check and slit with the pipe"*/

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_arg	op;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		ft_bzero(&op, sizeof(op));
		line = readline("> ");
		if (line)
			add_history(line);
		if (check_op(line, &op) > 1)// FREE LINE 
			continue ;
		if (ft_split_cmd(line, '|', op) == NULL)

		if (ft_strncmp(line, "exit", 5) == 0)
		{
			free(line);
			return (0);
		}
	}
	return (0);
}
