/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_thefd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:15:55 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/02 16:11:46 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inside_thefill(char *io_here, char *line)
{
	if (ft_strncmp(io_here, line, ft_strlen(io_here)) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	write_the(int fd, char *line, char *io_here, int param)
{
	if (param == 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (param == 1)
	{
		if (g_return_value != 130)
		{
			write(1, "minishell: warning: here-document ", 34);
			write(1, "delimited by end-of-file ", 25);
			printf ("(wanted `%s')\n", io_here);
		}
		return (1);
	}
	return (0);
}

int	if_the_same(char *io_here, char *line)
{
	if (ft_strncmp(io_here, line, (ft_strlen(line) + 1)) == 0)
	{
		free(line);
		return (0);
	}
	return (1);
}

void	init(int *i)
{
	*i = 0;
	handle_signal(HEREDOC);
}

int	fill_thefd(t_cmd cmd)
{
	int		fd;
	int		i;
	char	*line;

	init(&i);
	g_return_value = 0;
	while (cmd.here_words && g_return_value != 130)
	{
		if (fd_neg(&fd) == -1)
			return (-1);
		while (g_return_value != 130)
		{
			line = readline("> ");
			if (line && g_return_value != 130)
			{
				if (if_the_same(cmd.io_here[i], line) == 0)
					break ;
			}
			else if (line == NULL)
				if (write_the(fd, line, cmd.io_here[i], 1) == 1)
					break ;
			write_the(fd, line, cmd.io_here[i], 0);
		}
		plus_plus(&i, &cmd.here_words, fd);
	}
	return (fd);
}
