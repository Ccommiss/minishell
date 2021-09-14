/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:48:54 by ccommiss          #+#    #+#             */
/*   Updated: 2021/07/22 16:59:24 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_quit(char *err, t_cmd *cmd, int **fd)
{
	if (errno != 0)
		perror("Erreur");
	if (err)
		ft_putendl_fd(err, 2);
	if (fd || cmd)
		free_fds(fd, cmd);
	exit(1);
}

void	get_file(int file[2], char **argv, int ac)
{
	if (ac < 5)
		error_quit(USAGE, NULL, NULL);
	if (access(argv[1], R_OK) == -1)
		error_quit(FILE, NULL, NULL);
	file[INFILE] = open(argv[1], O_RDWR);
	if (file[INFILE] == -1 || access(argv[1], R_OK) == -1)
		error_quit(FILE, NULL, NULL);
	file[OUTFILE] = open(argv[ac - 1], O_RDWR | O_CREAT);
	if (file[OUTFILE] == -1)
		error_quit(OUTFILE_FAIL, NULL, NULL);
}

void	pipe_fds(int ***fd, int pipes)
{
	int	j;

	j = 0;
	*fd = malloc(sizeof(int *) * pipes);
	if (!fd)
		error_quit(MALLOC_ERR, NULL, *fd);
	while (j < pipes)
	{
		fd[0][j] = malloc(sizeof(int) * 2);
		pipe(fd[0][j]);
		j++;
	}
}
