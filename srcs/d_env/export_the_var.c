/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_the_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:23:21 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/22 14:47:45 by mpochard         ###   ########.fr       */
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


int	count_tab(char **tab)
{
	int i;

	i = 0;
	printf("yoloooooo %zu\n",ft_strlen(tab[i]));
	while (tab[i])
	{
		i++;
	}
		return (i);
}

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
	env->key = tab[0];
	env->value = tab[1];
	env->env = strjoin_char(tab[0], tab[1], '=');
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
		if (ft_strncmp(env->key, tab[0], ft_strlen(env->key)) == 0)
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
			if (cmd_suffix[0][k] == '\0') /// CLAIRE POUR COMPIL LINUX
				return (error);
			continue ;
		}
		if (ft_parse_concate(cmd_suffix[k]) == 1)
			egal = 2;
		else if (ft_isin('=', cmd_suffix[k]) == 1)
			egal = 1;
		else
			egal = 0;
		if (remplace(tmp, egal, cmd_suffix[k]) == 0)
		{
			if (egal == 1 || egal == 2)
				ft_lstadd_backenv(&env, ft_lstenv(cmd_suffix[k]));
			else if (egal == 0)
				ft_lstadd_backenv(&env, ft_lstenv_inv(cmd_suffix[k]));
		}
		k++;
	}
	return (error);
}
