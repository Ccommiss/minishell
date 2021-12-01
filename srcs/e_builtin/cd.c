/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:41:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/01 14:14:18 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	is_home_unset(t_env *tmp, char *home)
{
	t_env	*temp;

	temp = tmp;
	while (temp)
	{
		if (ft_strncmp(temp->key, "HOME", ft_strlen(temp->key)) == 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		return (no_home(home));
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", ft_strlen("OLDPWD")) == 0)
		{
			if (set_the_oldpwd(tmp, home) == -1)
				return (-1);
			break ;
		}
		tmp = tmp->next;
	}
	if (chdir(temp->value) == -1)
		perror("cd:");
	free(home);
	return (0);
}

int	set_home(t_env *env, char **home)
{
	t_env	*tmp1;

	tmp1 = env;
	while (tmp1)
	{
		if (strcmp(tmp1->key, "PWD") == 0)
			break ;
		tmp1 = tmp1->next;
	}
	if (tmp1 == NULL)
		*home = ft_strdup("");
	else
		*home = ft_strdup(tmp1->value);
	return (0);
}

int	on_coupe(t_env *env, char *pwd, char *home, char *temp)
{
	if (ft_strncmp(pwd, "~", 2) == 0)
	{
		if (chdir((getenv("HOME"))) == -1)
			return (error_chdir(temp, home));
	}
	else if (ft_strncmp(pwd, "-", 2) == 0)
	{
		if (env != NULL)
		{
			if (chdir(temp) == -1)
				return (error_chdir(temp, home));
		}
		else if (env == NULL)
			write(2, ">: cd: « OLDPWD » non defini\n", 2);
	}
	else if (chdir(pwd) == -1)
		return (error_chdir(temp, home));
	free(home);
	free(temp);
	return (0);
}

int	with_home_set(t_env *env, char *home, char **temp)
{
	*temp = ft_strdup(env->value);
	free(env->value);
	free(env->env);
	free(env->key);
	env->key = ft_strdup("OLDPWD");
	env->value = ft_strdup(home);
	env->env = strjoin_char(env->key, env->value, '=');
	if (env->key == NULL || env->value == NULL || env->env == NULL)
	{
		perror("malloc failed");
		if (env->key != NULL)
			free(env->key);
		if (env->value != NULL)
			free(env->value);
		if (env->env != NULL)
			free(env->env);
		env->value = NULL;
		env->key = NULL;
		env->env = NULL;
		return (-1);
	}
	return (0);
}

int	cd(t_env *env, char *pwd)
{
	char	*home;
	char	*temp;

	set_home(env, &home);
	if (pwd == NULL)
	{
		if (is_home_unset(env, home) == -1)
			return (-1);
	}
	else
	{
		while (env)
		{
			if (strcmp(env->key, "OLDPWD") == 0)
			{
				if (with_home_set(env, home, &temp) == -1)
					return (-1);
				break ;
			}
			env = env->next;
		}
		if (on_coupe(env, pwd, home, temp) == -1)
			return (-1);
	}
	return (0);
}
