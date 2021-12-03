/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:52:03 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/03 16:52:05 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env(t_env *env)
{
	void	*tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		free(env->env);
		tmp = env->next;
		free(env);
		env = tmp;
	}
}

void	free_toks(t_token *toks)
{
	t_token	*tmp;
	int		old_i;

	while (toks && toks->index > 0 && toks->index != 0)
		toks = toks->prev;
	while (toks)
	{
		tmp = toks;
		toks = toks->next;
		if (tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		old_i = tmp->index;
		tmp->index = -1;
		if (old_i != 0)
		{
			free(tmp);
			tmp = NULL;
		}		
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd && cmd->index >= 0)
	{
		if (cmd->cmd_args)
			ft_free_double_tab(cmd->cmd_args);
		if (cmd->cmdp)
			free(cmd->cmdp);
		if (cmd->io_here)
			ft_free_double_tab(cmd->io_here);
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->index > 0)
			free ((void *)tmp);
	}
}

int	free_and_return(void *stuff, int ret)
{
	free(stuff);
	stuff = NULL;
	return (ret);
}

void	cleanup(t_cmd *cmd, t_token *toks, char *line)
{
	free_cmds(cmd);
	if (toks->index != -1)
		free_toks(toks);
	free(line);
}
