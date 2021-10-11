/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:06:05 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/30 15:44:48 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_split_one_egal(char *str)
{
	int		i;
	int		j;
	char	**tab;
	int		count;

	i = 0;
	j = 0;
	count = 0;
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

void	get_the_env(t_env **envp, char **env)
{
	int		i;
	t_env	*temp;

	i = 0;
	while (env[i])
	{
		ft_lstadd_backenv(envp, ft_lstenv(env[i]));
		i++;
	}
}

void	printf_the_env(t_env *envp)
{
	t_env	*temp;

	temp = envp;
	while (envp)
	{
		if (strcmp (envp->key, "_") != 0)
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
