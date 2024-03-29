/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_the_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:23:21 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/03 18:41:19 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*'
 * on parse le cmd_suffix pour savoir si il y a un = et on split dessus
 */

/*
int	export_visible(char *cmd_suffix, t_env *env)
{
	char	*cmd;

	cmd = ft_strdup(cmd_suffix);
	ft_lstadd_backenv(&env, ft_lstenv_inv(cmd));
	return (1);
}*/

void	ft_concatene_exp(t_env *env, char **tab)
{
	char	*temp;

	free(env->key);
	env->key = tab[0];
	temp = ft_strdup(env->value);
	free(env->value);
	env->value = ft_strjoin(temp, tab[1]);
	free(env->env);
	env->env = strjoin_char(env->key, env->value, '=');
	free(temp);
}

int	need_replace(t_env *env, char **tab, int egal)
{
	if (egal == 0)
	{
		ft_free_double_tab(tab);
		return (1);
	}
	if (egal == 2)
	{
		ft_concatene_exp(env, tab);
		return (1);
	}
	if ((env->visible == 1 || env->visible == -1
			|| env->visible == -2) && egal == 1)
		env->visible = 0;
	free(env->key);
	free(env->value);
	free(env->env);
	env->key = ft_strdup(tab[0]);
	env->value = ft_strdup(tab[1]);
	env->env = strjoin_char(env->key, env->value, '=');
	ft_free_double_tab(tab);
	return (1);
}

int	remplace(t_env *env, int egal, char *cmd_suffix)
{
	char	**tab;

	tab = ft_split_one_egal(cmd_suffix);
	if (tab == NULL)
	{
		perror("malloc failed\n");
		return (-1);
	}
	while (env)
	{
		if (ft_strncmp(env->key, tab[0], ft_strlen(tab[0])) == 0)
		{
			return (need_replace(env, tab, egal));
		}
		env = env->next;
	}
	ft_free_double_tab(tab);
	return (0);
}
/*
 * egal 1  c'est qu'il a a=b
 * egal2 a+=b 
 * egal 0 a 
 *
 * */

void	put_in_list(t_env **env, char *cmd_suffix, int egal)
{
	if (egal == 1 || egal == 2)
		ft_lstadd_backenv(env, ft_lstenv(cmd_suffix));
	else if (egal == 0)
		ft_lstadd_backenv(env, ft_lstenv_inv(cmd_suffix));
}

int	export_the(t_env *env, char	**cmd_suffix)
{
	int		k;
	int		egal;
	t_env	*tmp;
	int		error;

	tmp = env;
	k = 0;
	error = 0;
	if (count_double_tab(cmd_suffix) == 0)
		return (print_the_export(env));
	while (cmd_suffix[k])
	{
		if (parse_cmd_suf(cmd_suffix[k]) == -1)
		{
			error = -1;
			k++;
			continue ;
		}
		egal = find_value_egal(cmd_suffix[k]);
		if (remplace(tmp, egal, cmd_suffix[k]) == 0)
			put_in_list(&env, cmd_suffix[k], egal);
		k++;
	}
	return (error);
}
