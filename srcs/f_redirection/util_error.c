/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:11:21 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 18:11:42 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_fail_d(char *str, int fd, int fd1, char **tenvp)
{
	perror(str);
	close(fd);
	close(fd1);
	ft_free_double_tab(tenvp);
	return (-1);
}

int	no_cmd_d(int fd, int fd1, int error)
{
	close(fd);
	close(fd1);
	if (error == 1)
		return (-1);
	return (0);
}

int	no_cmd(int fd, int error)
{
	close(fd);
	if (error == 1)
		return (-1);
	return (0);
}

int	fork_fail(char *str, int fd, char **tenvp)
{
	perror(str);
	close(fd);
	ft_free_double_tab(tenvp);
	return (-1);
}