/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:49:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/30 17:25:12 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	need_to_unset(t_env *env, char *cmd_suffix)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (strcmp(temp->key, cmd_suffix) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	case_of_sh(t_env *temp)
{
	temp->visible = -1;
	free(temp->value);
	temp->value = ft_itoa(0);
	free(temp->env);
	temp->env = strjoin_char(temp->key, temp->value, '=');
	if (temp->env == NULL)
	{
		free(temp->value);
		return (-1);
	}
	return (0);
}

int	case_pwd(t_env *temp, int param)
{
	if (param == 0)
	{
		temp->visible = -1;
		free(temp->value);
		temp->value = ft_strdup("");
	}
	else if (param == 1)
	{
		temp->visible = -2;
		free(temp->value);
		temp->value = ft_strdup("");
	}
	if (temp->value == NULL)
	{
		free(temp->key);
		temp->key = NULL;
		temp->value = NULL;
		temp->env = NULL;
		return (-1);
	}
	return (0);
}

int	unset_the_var(t_env *env, char *cmd_suffix)
{
	t_env	*temp;
	int		i;

	temp = env;
	i = 0;
	while (temp)
	{
		if ((ft_strncmp(temp->key, cmd_suffix,
					ft_strlen(cmd_suffix)) == 0) && i == 0)
			return (case_first(temp));
		else if (ft_strncmp(cmd_suffix, "PWD", 4) == 0
			&& ft_strncmp(temp->key, "PWD", 4) == 0)
			return (case_pwd(temp, 0));
		else if (ft_strncmp(cmd_suffix, "OLDPWD", 7) == 0
			&& ft_strncmp(temp->key, "OLDPWD", 7) == 0)
			return (case_pwd(temp, 1));
		else if (ft_strncmp(cmd_suffix, "SHLVL", 6) == 0
			&& ft_strncmp(temp->key, "SHLVL", 6) == 0)
			return (case_of_sh(temp));
		else if (ft_strncmp(temp->key, cmd_suffix, ft_strlen(cmd_suffix)) == 0)
			return (delete_the_node(&env, temp));
		i++;
		temp = temp->next;
	}
	return (0);
}

int	do_the_unset(t_env *env, char **cmd_suffix)
{
	int		i;
	int		error;

	i = 0;
	error = 0;
	if (cmd_suffix == NULL)
		return (error);
	while (cmd_suffix[i])
	{
		if (check_the_cmd(cmd_suffix[i]) == -1)
			error = -1;
		i++;
	}
	i = 0;
	while (cmd_suffix[i])
	{
		if (need_to_unset(env, cmd_suffix[i]) == 1)
			unset_the_var(env, cmd_suffix[i]);
		i++;
	}
	return (error);
}
