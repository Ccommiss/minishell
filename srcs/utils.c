#include "minishell.h"

void cleanup(t_cmd *cmd, t_token *toks, char *line)
{
	int i;

	while (cmd)
	{
		i = 0;
		printf("%s \n", cmd->cmd_args[0]);
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
	(void)toks; // appeler fo free
	free(line);
}
