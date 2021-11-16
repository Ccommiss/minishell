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

int	fd_neg(int fd)
{
	if (fd == -1)
	{
		perror(">");
		return (-1);
	}
	return (0);
}

void	write_the(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

void	plus_plus(int *i, int *here_word, int fd)
{
	*i += 1;
	*here_word -= 1;
	close(fd);
}/*
int	fill_thefd(t_cmd cmd)
{
	int		fd;
	int		i;
	int		ret;
	char	*line;

	i = 0;
	while (cmd.here_words)
	{
		fd = open(".here_doc", O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (fd_neg(fd) == 0)
		{
			while ((ret = (get_next_line(0, &line))))
			{
				printf("line %s\n",line);
				if (line)
				{
					if (inside_thefill(cmd.io_here[i], line) == 1)
						break ;
					write_the(fd, line);
				}
			}
		}
		plus_plus(&i, &cmd.here_words, fd);
	}
	return (fd);
}*/

int	fill_thefd(t_cmd cmd)
{
	int		fd = 0;
	int		i;
	char	*line;

	i = 0;
	while (cmd.here_words)
	{
		fd = open(".here_doc", O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (fd_neg(fd) == 0)
		{
			while (1)
			{
				line = readline(">");
				if (!line)
				{
					free(line);
					break;
				}
					if (line)
				{
					if (inside_thefill(cmd.io_here[i], line) == 1)
					{

						break ;
					}
					write_the(fd, line);
				}
			}
		}
		plus_plus(&i, &cmd.here_words, fd);
	}
	return (fd);
}
