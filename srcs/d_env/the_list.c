/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:41:11 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/08 14:45:21 by mpochard         ###   ########.fr       */
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

void	ft_lstadd_backenv(t_env **alst, t_env *nev)
{
	t_env	*last;

	if (*alst != NULL)
	{
		last = ft_lstlastenv(*(alst));
		last->next = nev;
		nev->prev = last;
	}
	else
	{
		nev->prev = NULL;
		*alst = nev;
	}
}

t_env	*ft_lstenv(char *content)
{
	char	**tab;
	t_env	*res;

	res = malloc(sizeof(t_env));
	if (!(res))
		return (NULL);
	tab = ft_split_one_egal(content);
	if (tab == NULL)
		return (NULL);
	res->key = tab[0];
	res->value = tab[1];
	res->env = strjoin_char(res->key, res->value, '=');
	res->visible = 0;
	res->next = 0;
	return (res);
}
t_env	*ft_lstenv_inv(char *content)
{
	t_env	*res;

	res = malloc(sizeof(t_env));
	if (!(res))
		return (NULL);
	res->key = ft_strdup(content);
	res->env = ft_strdup(content);
	res->visible = 1;
	res->value = ft_strdup("");
	res->next = 0;
	return (res);
}

