#include "minishell.h"

void	command_and_suffix(t_cmd *cmd, t_token *toks, int *j)
{
	cmd->cmd_args = (char **)ft_realloc_double_pointer((void **)cmd->cmd_args,
			(sizeof(char **) * (*j + 1)), (sizeof(char **) * (*j + 2)));
	cmd->cmd_args[*j] = ft_strdup(toks->content);
	*j += 1;
	cmd->cmd_args[*j] = NULL;
}
