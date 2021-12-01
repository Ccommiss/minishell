#include "minishell.h"

void	init_token(t_token *toks)
{
	toks->index = -1;
	toks->content = NULL;
	toks->len = -1;
	toks->type = -1;
	toks->prev = NULL;
	toks->next = NULL;
}

void	start_cmd(t_cmd *cmd)
{
	cmd->cmd_args = NULL;
	cmd->cmdp = NULL;
	cmd->index = -1;
	cmd->prev = NULL;
	cmd->io_in = NOT_SPECIFIED;
	cmd->io_out = NOT_SPECIFIED;
	cmd->dgreat = FALSE;
	cmd->dless = FALSE;
	cmd->error = FALSE;
}

void	init_tok_and_cmd(t_token *toks, t_cmd *cmd)
{
	init_token(toks);
	start_cmd(cmd);
}
