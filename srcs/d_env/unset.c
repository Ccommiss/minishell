/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:49:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/16 11:48:54 by mpochard         ###   ########.fr       */
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

void	delete_the_node(t_env **env, t_env *del)
{
	if (*env == NULL || del == NULL)
		return ;
	if (*env == del)
		*env = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del);
	return ;
}

int	unset_the_var(t_env *env, char *cmd_suffix)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (strncmp(cmd_suffix, "PWD", 3) == 0 && strcmp(temp->key, "PWD") == 0)
		{
			free(temp->value);
			temp->visible = -1;
			temp->value = ft_strdup("");
			return (0);
		}
		else if(strcmp(cmd_suffix, "OLDPWD") == 0 && strcmp(temp->key, "OLDPWD") == 0)
		{
			temp->visible = -2;
			free(temp->value);
			temp->value = ft_strdup("");
			return (0);
	}
		if (strncmp(cmd_suffix, "SHLVL", 6) == 0 && ft_strncmp(temp->key, "SHLVL", 6) == 0)
		{
			temp->visible = -1;
			free(temp->value);
			temp->value = ft_itoa(0);
			free(temp->env);
			temp->env = strjoin_char(temp->key, temp->value, '=');
			return (0);
		}
		else if (strcmp(temp->key, cmd_suffix) == 0)
		{
			delete_the_node(&env, temp);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int		check_the_cmd(char *cmd_suffix)
{
	int	i;

	if (ft_isalpha(cmd_suffix[0]) == 0)
	{
		printf(" unset: '%s': not a valid identifier\n", cmd_suffix);
		return (-1);
	}
	i = 1;
	while (cmd_suffix[i])
	{
		if (ft_isalnum(cmd_suffix[i]) == 0)
		{
			printf(" unset: '%s': not a valid identifier\n", cmd_suffix);
			return (-1);
		}
			i++;
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
