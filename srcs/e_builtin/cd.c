/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:41:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/12 18:12:32 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

char	*get_pwd(void)
{
	char	*tmp;
	char	buf[PATH_MAX + 1];
	
	getcwd(buf, PATH_MAX);
	tmp = ft_strdup(buf);
	return (tmp);
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

int	is_home_unset(t_env *tmp, char *home)
{
	t_env *temp;

	temp = tmp;
	while (temp)
	{
		if (strcmp(temp->key, "HOME") == 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
	{
		write(1, "cd: HOME not set\n", 17);
		return (-1);
	}
	while (tmp)
	{
			if (strcmp(tmp->key, "OLDPWD") == 0)
			{
				free(tmp->value);
				tmp->value = home;
				if (tmp->visible == -1)
					tmp->visible = 0;
				tmp->env = strjoin_char(tmp->key, tmp->value, '=');
				break ;
			}
			tmp = tmp->next;
		}
	if (chdir(temp->value) == -1)
		perror("cd:");
	return (0);
}

int	cd(t_env *env, char *pwd)
{
	t_env	*tmp;
	char	*home;
	t_env	*tmp1;
	void	*temp;

	tmp = env;
	tmp1 = env;
	temp =NULL;
	while(tmp1)
	{
		if (strcmp(tmp1->key, "PWD") == 0)
			break;
		tmp1 = tmp1->next;
	}
	if (tmp1== NULL)
		home = ft_strdup("");
	else
		home = tmp1->value;
	if (pwd == NULL)
	{
		
		if (is_home_unset(tmp,home) == -1)
			return (-1);
	}
	else 
	{
		while (env)
		{
			if (strcmp(env->key, "OLDPWD") == 0)
			{
				temp = ft_strdup(env->value);
				free(env->value);
				env->value = home;
				env->env = strjoin_char(env->key, env->value, '=');
				break ;
			}
			env = env->next;
		}
			if (ft_strncmp(pwd,"~", 2) == 0)
			{
				if (chdir((getenv("HOME"))) == -1)
				{
					perror("cd:");
					free(temp);
					return (-1);
				}
			}
			else if (ft_strncmp(pwd,"-", 2) == 0)
			{
				if (env != NULL)
				{
					if (chdir(temp) == -1)
					{
						perror("cd:");
						free(temp);
						return (-1);
					}
				}
				else if ( env == NULL)
					write(2,">: cd: « OLDPWD » non defini\n",2);
			}
			else
				if (chdir(pwd) == -1)
				{
					perror("cd:");
					free(temp);
					return (-1);
				}
		free(temp);
	}
		return (0);
}

void	set_thepwd(t_env *env)
{
	while (env)
	{
		if (strcmp(env->key, "PWD") == 0)
		{
			env->value = get_pwd();
			env->env = strjoin_char(env->key, env->value, '=');
			break ;
		}
		env = env->next;
	}
}
