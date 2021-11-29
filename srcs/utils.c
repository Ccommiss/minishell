#include "minishell.h"

void free_toks(t_token *toks)
{
	t_token *tmp;

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
		if (tmp->index != 0)
		{
			tmp->index = -1;
			free(tmp);
			tmp = NULL;
		}
	}
}

void free_cmds(t_cmd *cmd)
{
	int i;
	t_cmd *tmp;

	while (cmd && cmd->index >= 0)
	{
		i = 0;
		if (cmd->cmd_args)
		{
			while (cmd->cmd_args[i])
				free(cmd->cmd_args[i++]);
			free(cmd->cmd_args);
			cmd->cmd_args = NULL;
		}
		if (cmd->cmdp)
			free(cmd->cmdp);
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->index > 0)
		free((void*)tmp);
	}
}


void	ft_print_error(char *arg)
{
	if (arg != NULL)
		printf("minishell: %s: %s\n", arg, strerror(errno));
	else
		printf("minishell: %s\n", strerror(errno));

}

void cleanup(t_cmd *cmd, t_token *toks, char *line)
{
	free_cmds(cmd);
	// if (toks && toks->next)
	// 	free_toks(toks);
	(void)toks;
	free(line);
}
