/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:01:37 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/05 21:55:59 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_cmdp(t_cmd *cmds, char *path)
{
	int		j;
	char	**tab;
	char	*command_path;

	tab = ft_split(path, ':');
	while (cmds && path)
	{
		j = -1;
		while (tab[++j] != NULL && cmds->cmdp == NULL && cmds->cmd_args)
		{
			path = ft_strconcat(tab[j], "/", ft_strlen(tab[j]) + 1);
			command_path = ft_strconcat(path, cmds->cmd_args[0],
					ft_strlen(path) + ft_strlen(cmds->cmd_args[0]));
			free(path);
			if (access(command_path, F_OK) == 0)
				cmds->cmdp = ft_strdup(command_path);
			free(command_path);
		}
		cmds = cmds->next;
	}
	ft_free_double_tab(tab);
	tab = NULL;
}

/*
**	find path finds the path in the env to then set the
**	good path for each command.
**
**	If no PATH variable is founds in env, (unset PATH)
**	(env = NULL after all iteration through env keys), cmdp is set
**	to "".
*/

void	find_path(t_cmd *cmds, t_env *env)
{
	if (cmds->index == -1)
		return ;
	while (env && ft_strncmp(env->key, "PATH", 4) != 0)
		env = env->next;
	if (env != NULL)
		find_cmdp(cmds, env->value);
	else
		cmds->cmdp = ft_strdup("");
}
