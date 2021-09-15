/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 14:57:28 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/15 10:58:29 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

size_t		ft_newline(char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int			read_gnl(int fd, char **temp, char *buf, int *k)
{
	int		ret;
	char	*copy;

	while ((ret = read(fd, buf, 4096)))
	{
		if (ret == -1)
		{
			free(*temp);
			return (-1);
		}
		buf[ret] = '\0';
		copy = *temp;
		*temp = ft_strjoin(copy, buf);
		free(copy);
		if (*temp == NULL)
			return (-1);
		if ((*k = ft_newline(*temp, '\n')) >= 0)
			break ;
	}
	if (*k == -1)
		*k = ft_strlen(*temp);
	if (ret > 0)
		ret = 1;
	return (ret);
}

int			ft_error(char *str)
{
	free(str);
	return (-1);
}

void		endgnl(char *buf, char *str, int ret, int k)
{
	if (ret != 0)
		ft_strlcpy(buf, &str[k + 1], 4096 + 1);
	else
		ft_strlcpy(buf, "", 1);
	free(str);
}

int			get_next_line(int fd, char **line)
{
	static char		buf[4096 + 1] = "";
	char			*temp;
	int				k;
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	if ((temp = ft_strdup(buf)) == NULL)
		return (-1);
	if ((k = ft_newline(temp, '\n')) >= 0)
	{
		if (!(*line = ft_substr(temp, 0, k)))
			ft_error(temp);
		ret = 1;
	}
	else
	{
		if ((ret = read_gnl(fd, &temp, buf, &k)) == -1)
			return (-1);
		*line = ft_substr(temp, 0, k);
	}
	endgnl(buf, temp, ret, k);
	if (*line == NULL)
		return (-1);
	return (ret);
}
