/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:06:05 by mpochard          #+#    #+#             */
/*   Updated: 2021/10/13 16:35:19 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_one_egal(char *str)
{
	int		i;
	int		j;
	char	**tab;
	//int		count;

	i = 0;
	j = 0;
	//count = 0;
	tab = malloc(sizeof(char *) *(2 + 1));
	if (tab == NULL)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	tab[j] = strndup(str, i);
	j++;
	if (str[i] == '=')
		i++;
	tab[j] = ft_strdup(&str[i]);
	j++;
	tab[j] = 0;
	return (tab);
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

}

void	printf_the_env(t_env *envp)
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
}
