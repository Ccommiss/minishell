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
		// if (!toks)
		// 	printf("nulle add\n");
		// printf(" %p %p toks\n", toks, tmp);
	}
}

void free_cmds(t_cmd *cmd)
{
	int i;

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
		cmd = cmd->next;
	}
}




void cleanup(t_cmd *cmd, t_token *toks, char *line)
{
	free_cmds(cmd);
	// if (toks && toks->next)
	// 	free_toks(toks);
	(void)toks;
	free(line);
}
