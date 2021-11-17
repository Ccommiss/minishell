/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:06:05 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/12 17:38:51 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_one_egal(char *str)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) *(2 + 1));
	if (tab == NULL)
		return (NULL);
	while ((ft_isalnum(str[i]) == 1 || str[i] == '_') && str[i] != '=')
		i++;
	tab[j] = strndup(str, i);
	j++;
	if ( str[i] == '+')
		i++;
	if (str[i] == '=')
		i++;
	tab[j] = ft_strdup(&str[i]);
	j++;
	tab[j] = 0;
	return (tab);
}

static	void	init(int *i, int *k)
{
	*i = 0;
	*k = 0;
}

char	*ft_strjoin_char(char *str, char *str1, char c)
{
	int		i;
	int		j;
	int		k;
	char	*fi;

	init(&i, &k);
	j = ft_strlen(str) + ft_strlen(str1) + 1;
	fi = malloc(sizeof(char *) * (j + 1));
	if (!(fi))
		return (NULL);
	while (str[i])
	{
		fi[i] = str[i];
		i++;
	}
	fi[i] = c;
	i++;
	while (str1[k])
	{
		fi[i] = str1[k];
		k++;
		i++;
	}
	fi[i] = '\0';
	return (fi);
}

void	set_the_pwd_inv(t_env *env)
{
	while(env)
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
	t_env *tmp;
	int	temp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "SHLVL", 6) == 0)
			{
				free(tmp->env);
				temp = ft_atoi(tmp->value);
				free(tmp->value);
				tmp->value = ft_itoa((temp +1));
				if (tmp->value == NULL)
				{
					perror("malloc failed");
					return (-1);
				}
				tmp->env = ft_strjoin_char(tmp->key, tmp->value, '=');
			break;
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

int		printf_the_env(t_env *envp)
{
	t_env	*temp;

	temp = envp;
	while (envp)
	{
		if (envp->visible == 0 && strcmp (envp->key, "_") != 0 && envp->visible == 0)
			printf("%s\n", envp->env);
		envp = envp->next;
	}
	while (temp)
	{
		if (strcmp (temp->key, "_") == 0)
			printf("%s\n", temp->env);
		temp = temp->next;
	}
	return (0);
}
