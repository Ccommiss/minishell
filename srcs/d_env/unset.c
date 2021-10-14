/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:49:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/10/14 15:34:27 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	need_to_unset(t_env *env, char *cmd_suffix)
{
	int		i;
	t_env	*temp;

	i = 0;
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
		else if (strcmp(temp->key, cmd_suffix) == 0)
		{
			delete_the_node(&env, temp);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	check_the_cmd(char *cmd_suffix)
{
	int	i;

	i = 0;
	while (cmd_suffix[i])
	{
		if (cmd_suffix[i] == '=')
			printf(" unset: '%s': not a valid identifier\n", cmd_suffix);
		i++;
	}
}

void	do_the_unset(t_env *env, char **cmd_suffix)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	if (cmd_suffix == NULL)
		return ;
	while (cmd_suffix[i])
	{
		check_the_cmd(cmd_suffix[i]);
		i++;
	}
	i = 0;
	while (cmd_suffix[i])
	{
		if (need_to_unset(env, cmd_suffix[i]) == 1)
			unset_the_var(env, cmd_suffix[i]);
		i++;
	}
}