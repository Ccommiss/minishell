/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_the_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:23:21 by mpochard          #+#    #+#             */
/*   Updated: 2021/10/20 11:14:21 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*'
 * on parse le cmd_suffix pour savoir si il y a un = et on split dessus
 */
t_env	*test(t_env *env)
{
	t_env	*test;

	test = env;
	while (test->next)
	{
		test = test->next;
	}
	return (test);
}

int	export_the_var(t_env *env, char *cmd_suffix)
{
	int	i;

	i = 0;
	while (cmd_suffix[i])
	{
		if (cmd_suffix[i] == '=')
		{
			ft_lstadd_backenv(&env, ft_lstenv(cmd_suffix));
			return (0);
		}
		i++;
	}
	return (1);
}

int	remplace_the_var(t_env *env, char *cmd_suffix)
{
	int		i;
	char	**tab;

	i = 0;
	if ( cmd_suffix == NULL)
		return (print_the_export(env));
	while(cmd_suffix[i])
	{
		if (cmd_suffix[i] == '=')
			break;
		i++;
	}
	if ( (size_t)i == ft_strlen(cmd_suffix))
			return (-1);
	tab = ft_split_one_egal(cmd_suffix);
	while (env)
	{
		if (strcmp(env->key, tab[0]) == 0)
		{
			free(env->key);
			free(env->value);
			env->key = tab[0];
			env->value = tab[1];
			env->env = cmd_suffix;
			return (1);
		}
		env = env->next;
	}
	return (0);
}
