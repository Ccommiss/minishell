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
}

int fill_thefd(t_cmd cmd)
{
	int fd;
	int i;
	char *line;

	i = 0;
	//g_utils.g_sig = 0;
	handle_signal(HEREDOC);
	while (cmd.here_words && return_value != 130)
	{
		fd = open(".here_doc", O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (fd == -1)
		{
			perror(">");
			return (-1);
		}
		while (return_value != 130)
		{
			line = readline("> ");
			if (line && return_value != 130)
			{
				if (ft_strncmp(cmd.io_here[i], line, ft_strlen(cmd.io_here[i])) == 0)
				{
					free(line);
					break;
				}
			}
				else if (line == NULL)
				{
					if (return_value != 130)
						printf ("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", cmd.io_here[i]);
					break;
				}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		i++;
		cmd.here_words--;
		close(fd);
	}
	return (fd);
}
