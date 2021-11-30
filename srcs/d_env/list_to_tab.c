/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:42:23 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 17:23:38 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_of_arg(t_env *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (temp->visible == 0 || temp->visible == -1)
		{
			i++;
		}
		temp = temp->next;
	}
	return (i);
}

char	**list_to_cmd(t_env *env)
{
	int		nbr;
	char	**tab;
	t_env	*temp;

	temp = env;
	nbr = nbr_of_arg(temp);
	tab = malloc(sizeof(char *) * (nbr + 1));
	if (tab == NULL)
		return (NULL);
	nbr = 0;
	while (env)
	{
		if (env->visible == 0 || env->visible == -1)
		{
			tab[nbr] = ft_strdup(env->env);
			nbr++;
		}
		env = env->next;
	}
	tab[nbr] = 0;
	return (tab);
}