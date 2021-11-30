/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:06:05 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 17:23:18 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_the_pwd_inv(t_env *env)
{
	while (env)
	{
		if (strcmp(env->key, "OLDPWD") == 0)
		{
			env->visible = -1;
			break ;
		}
		env = env->next;
	}
}

int	shlvl(t_env *env)
{
	t_env	*tmp;
	int		temp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "SHLVL", 6) == 0)
		{
			free(tmp->env);
			temp = ft_atoi(tmp->value);
			free(tmp->value);
			tmp->value = ft_itoa((temp + 1));
			if (tmp->value == NULL)
			{
				perror("malloc failed");
				return (-1);
			}
			tmp->env = strjoin_char(tmp->key, tmp->value, '=');
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	get_the_env(t_env **envp, char **env)
{
	int		i;
	int		create;

	i = 0;
	create = -1;
	while (env[i])
	{
		if (strncmp(env[i], "OLDPWD", 6) == 0)
			create = 1;
		ft_lstadd_backenv(envp, ft_lstenv(env[i]));
		i++;
	}
	if (create == -1)
	{
		ft_lstadd_backenv(envp, ft_lstenv("OLDPWD= "));
		set_the_pwd_inv(*envp);
	}
	shlvl(*envp);
}

int	printf_the_env(t_env *envp, char **cmd)
{
	t_env	*temp;

	temp = envp;
	if (count_double_tab(cmd) > 1)
	{
		write(2, "env: ", 5);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, ": No such file or directory\n", 28);
		return (127);
	}
	while (envp)
	{
		if (envp->visible == 0 && ft_strncmp(envp->key, "_",
				ft_strlen(envp->key)) != 0 && envp->visible == 0)
			printf("%s\n", envp->env);
		envp = envp->next;
	}
	while (temp)
	{
		if (ft_strncmp (temp->key, "_", ft_strlen(temp->key)) == 0)
			printf("%s\n", temp->env);
		temp = temp->next;
	}
	return (0);
}