/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args_and_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:54:41 by ccommiss          #+#    #+#             */
/*   Updated: 2021/07/22 16:54:42 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_command(char **cmd, char ***args, char *path)
{
	int		j;
	char	**tab;
	char	*command_path;

	j = -1;
	*args = ft_split(*cmd, ' ');
	ft_memdel((void **)cmd);
	tab = ft_split(path, ':');
	while (tab[++j] != NULL)
	{
		path = ft_strconcat(tab[j], "/", ft_strlen(tab[j]) + 1);
		command_path = ft_strconcat(path, args[0][0],
				ft_strlen(path) + ft_strlen(args[0][0]));
		free(path);
		if (access(command_path, F_OK) == 0)
		{
			*cmd = ft_strdup(command_path);
			free(command_path);
			break ;
		}
		free(command_path);
	}
	ft_free_double_tab(tab);
	if (!*cmd)
		error_quit(CMD_ERR, NULL, NULL);
}

void	find_path(char **path, char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	*path = ft_strdup(envp[i]);
}

t_cmd	*take_multiple_args(char **argv, int ac, char **envp)
{
	int		i;
	char	*path;
	t_cmd	*cmds;
	t_cmd	*head;

	i = 1;
	cmds = malloc(sizeof(t_cmd));
	head = cmds;
	find_path(&path, envp);
	while (i < ac - 2)
	{
		cmds->index = i - 1;
		cmds->head = head;
		cmds->cmdp = ft_strdup(argv[i + 1]);
		find_command(&cmds->cmdp, &cmds->cmd_args, path);
		i++;
		cmds->next = NULL;
		if (i < ac - 2)
		{
			cmds->next = malloc(sizeof(t_cmd));
			cmds = cmds->next;
		}
	}
	free(path);
	return (head);
}
