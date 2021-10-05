/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:06:05 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/30 11:40:43 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstlastenv(t_env *lst)
{
	t_env	*ptr;

	ptr = lst;
	if (lst)
	{
		while (ptr->next)
		{
			ptr = ptr->next;
		}
	}
	return (ptr);
}

void	ft_lstadd_backenv(t_env **alst, t_env *new)
{
	t_env	*last;

	if (*alst)
	{
		last = ft_lstlastenv(*(alst));
		last->next = new;
	}
	else
		*alst = new;
}

t_env	*ft_lstenv(char *content)
{
	char	**tab;
	t_env	*res;

	res = malloc(sizeof(t_env));
	if (!(res))
		return (NULL);
	tab = ft_split(content, '=');
	if ( tab == NULL)
		return (NULL);
	res->key = tab[0];
	res->env = content;
	res->value = tab[1];
	res->next = 0;
	return (res);
}

void	get_the_env(t_env **envp, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_backenv(envp, ft_lstenv(env[i]));
		i++;
	}
}

void	printf_the_env(t_env *envp)
{
	while(envp)
	{
		printf("%s\n",envp->env);
		envp = envp->next;
	}
}
