#include "minishell.h"

void	find_cmdp(t_cmd *cmds, char *path)
{
	int		j;
	char	**tab;
	char	*command_path;

	j = -1;
	tab = ft_split(path, ':');
    while (cmds) 
    {
        if (cmds->cmd_args != NULL && access(cmds->cmd_args[0], F_OK) == 0)
            cmds->cmdp = ft_strdup(cmds->cmd_args[0]);
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
        //ft_free_double_tab(tab);
        cmds = cmds->next;
        j = -1;
    }
}


void	find_path(t_cmd *cmds, t_env *env)
{
	while (env && ft_strncmp(env->key, "PATH", 4) != 0)
		env = env->next;
	find_cmdp(cmds, env->value);
}