/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 14:57:28 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/16 14:14:52 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_newline(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_error(char *str)
{
	free(str);
	return (-1);
}

int	read_gnl(int fd, char **temp, char *buf, int *k)
{
	int		ret;
	char	*copy;

	ret = 1;
	while (ret)
	{
		ret = read(fd, buf, 4096);
		if (ret == -1)
			return (ft_error(*temp));
		buf[ret] = '\0';
		copy = *temp;
		*temp = ft_strjoin(copy, buf);
		free(copy);
		if (*temp == NULL)
			return (-1);
		*k = ft_newline(*temp, '\n');
		if (*k >= 0)
			break ;
	}
	if (*k == -1)
		*k = ft_strlen(*temp);
	if (ret > 0)
		ret = 1;
	return (ret);
}

void	endgnl(char *buf, char *str, int ret, int k)
{
	if (ret != 0)
		ft_strlcpy(buf, &str[k + 1], 4096 + 1);
	else
		ft_strlcpy(buf, "", 1);
	free(str);
}

int	get_next_line(int fd, char **line)
{
	static char		buf[4096 + 1] = "";
	t_gnl			utils;

	if (fd < 0 || !line)
		return (-1);
	utils.temp = ft_strdup(buf);
	utils.k = ft_newline(utils.temp, '\n');
	if (utils.k >= 0)
	{
		*line = ft_substr(utils.temp, 0, utils.k);
		if (!(*line))
			ft_error(utils.temp);
		utils.ret = 1;
	}
	else
	{
		utils.ret = read_gnl(fd, &utils.temp, buf, &utils.k);
		if (utils.ret == -1)
			return (-1);
		*line = ft_substr(utils.temp, 0, utils.k);
	}
	endgnl(buf, utils.temp, utils.ret, utils.k);
	if (*line == NULL)
		return (-1);
	return (utils.ret);
}
