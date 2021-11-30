/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:35:37 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 17:35:55 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	*tmp;
	char	buf[PATH_MAX + 1];

	getcwd(buf, PATH_MAX);
	tmp = ft_strdup(buf);
	return (tmp);
}

void	set_thepwd(t_env *env)
{
	while (env)
	{
		if (strcmp(env->key, "PWD") == 0)
		{
			free(env->key);
			free(env->value);
			free(env->env);
			env->key = ft_strdup("PWD");
			env->value = get_pwd();
			env->env = strjoin_char(env->key, env->value, '=');
			break ;
		}
		env = env->next;
	}
}

int	set_the_oldpwd(t_env *tmp, char *home)
{
	free(tmp->value);
	free(tmp->env);
	free(tmp->key);
	tmp->key = ft_strdup("OLDPWD");
	tmp->value = ft_strdup(home);
	if (tmp->visible == -1)
		tmp->visible = 0;
	tmp->env = strjoin_char(tmp->key, tmp->value, '=');
	if (tmp->key == NULL || tmp->value == NULL || tmp->env == NULL)
	{
		if (tmp->key != NULL)
			free(tmp->key);
		if (tmp->value != NULL)
			free(tmp->value);
		if (tmp->env != NULL)
			free(tmp->env);
		tmp->value = NULL;
		tmp->env = NULL;
		tmp->key = NULL;
		free(home);
		return (-1);
	}
	return (0);
}