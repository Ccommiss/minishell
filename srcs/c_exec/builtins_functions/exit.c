/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:24:22 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/07 11:26:12 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	error_num(char *str, t_env *env, int param)
{
	if (param == 0)
	{
		write(2, "Minishell: exit: ", 17);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	else if (param == 1)
	{
		write(2, "Minishell: exit: ", 17);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 28);
		clean_env(env);
		exit(2);
	}
}

int	error_count(char *str, t_env *env, int param)
{
	if (if_num(str) == 1)
	{
		write(2, "Minishell: exit: too many arguments\n", 36);
		if (g_return_value >= 1)
			return (1);
		else
		{
			g_return_value = 1;
			return (1);
		}
	}
	else
		error_num(str, env, param);
	return (0);
}

void	exito(char **cmd_suff, t_cmd *cmd, t_env *env, char *line)
{
	char	n;
	int		count;

	(void)line;
	(void)cmd;
	count = count_double_tab(cmd_suff);
	if (isatty(1) && isatty(0))
		write(1, "exit\n", 5);
	if (cmd_suff[1] == NULL)
	{
		clean_env(env);
		exit(g_return_value);
	}
	if (count > 2)
	{
		if (error_count(cmd_suff[1], env, 1) == 1)
			return ;
	}
	if (if_num(cmd_suff[1]) == 0)
		error_num(cmd_suff[1], env, 1);
	clean_env(env);
	n = (char)ft_atoi(cmd_suff[1]);
	exit(n);
}
