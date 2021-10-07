#include "minishell.h"

void	redirect(t_cmd *cmd, t_token *toks, int type, int len)
{
	if (!toks->next)
		return ((void)0);
	toks = toks->next;
	if (type == TOK_LESS)
	{
		if (len == 1)
			cmd->io_in = open(toks->content, O_RDWR | O_TRUNC | O_CREAT);
		if (len == 2)
			cmd->io_in = open(toks->content, O_RDWR | O_APPEND | O_CREAT);
	}
	if (type == TOK_GREAT)
	{
		if (len == 1)
			cmd->io_out = open(toks->content, O_RDWR | O_TRUNC | O_CREAT);
		if (len == 2)
			cmd->io_out = open(toks->content, O_RDWR | O_APPEND | O_CREAT);
	}
}

void	command_and_suffix(t_cmd *cmd, t_token *toks, int *j)
{
	cmd->cmd_args = realloc(cmd->cmd_args, (sizeof(char **) * (*j + 2)));
	cmd->cmd_args[*j] = ft_strdup(toks->content);
	*j += 1;
	cmd->cmd_args[*j] = NULL;
}

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd_args = malloc(sizeof(char **) * 1);
	cmd->index = 0;
	if (cmd->prev != NULL)
		cmd->index = cmd->prev->index + 1;
	cmd->io_in = NOT_SPECIFIED;
	cmd->io_out = NOT_SPECIFIED;
	cmd->dgreat = FALSE;
	cmd->dless = FALSE;
}

t_cmd	*token_to_cmds(t_cmd *cmd, t_token *toks)
{
	int	j;

	j = 0;
	init_cmd(cmd);
	if (toks->type == TOK_PIPE)
		toks = toks->next;
	while (toks && toks->type != TOK_PIPE)
	{
		if (toks->type == TOK_WORD)
			command_and_suffix(cmd, toks, &j);
		if (toks->type == TOK_LESS || toks->type == TOK_GREAT)
			redirect (cmd, toks, toks->type, ft_strlen(toks->content));
		toks = toks->next;
	}
	if (toks != NULL && !(toks->type == TOK_PIPE && !toks->next))
	{
		cmd->next = malloc(sizeof(t_cmd));
		cmd->next->prev = cmd;
		token_to_cmds(cmd->next, toks);
	}
	else
		cmd->next = NULL;
	return (cmd);
}
