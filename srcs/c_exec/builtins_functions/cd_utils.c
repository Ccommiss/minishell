/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:33:52 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/07 10:58:03 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_chdir(char *str, char *home, char *pwd)
{
	write(2, "Minishell: cd: ", 15);
	write(2, pwd, ft_strlen(pwd));
	write(2, ": ", 2);
	perror("");
	free(home);
	free(str);
	return (-1);
}

int	no_home(char *home)
{
	write(1, "cd: HOME not set\n", 17);
	free(home);
	return (-1);
}

char	*strjoin_char(char *str, char *str1, char c)
{
	char	*final;
	int		i;
	int		j;

	i = 0;
	j = 0;
	final = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(str1) + 2)));
	if (final == NULL)
		return (NULL);
	while (str[i])
	{
		final[j] = str[i];
		i++;
		j++;
	}
	final[j++] = c;
	i = 0;
	while (str1[i])
	{
		final[j] = str1[i];
		j++;
		i++;
	}
	final[j] = '\0';
	return (final);
}

int	cd_too_many_arg(void)
{
	write(2, "Minishell: cd:", 15);
	write(2, " too many arguments\n", 20);
	return (-1);
}

void	error_cd(char *home)
{
	write(2, "Minishell: cd: ", 14);
	write(2, home, ft_strlen(home));
	write(2, ": ", 2);
	perror("");
}
