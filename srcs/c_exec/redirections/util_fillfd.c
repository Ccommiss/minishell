/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_fillfd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:11:57 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/08 16:30:10 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_neg(int *fd)
{
	*fd = open(".here_doc", O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (*fd == -1)
	{
		perror(">");
		return (-1);
	}
	return (0);
}

void	plus_plus(int *i, int *here_word, int fd)
{
	*i += 1;
	*here_word -= 1;
	close(fd);
}

void	close_and_free(char **tenvp, t_cmd cmd)
{
	ft_free_double_tab(tenvp);
	if (cmd.io_out > 0)
		close(cmd.io_out);
	if (cmd.io_in > 0)
		close(cmd.io_in);
}
