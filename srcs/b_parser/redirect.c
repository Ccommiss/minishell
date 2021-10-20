#include "minishell.h"

void redirect_out(t_cmd *cmd, t_token **toks, int len)
{
	if (len == 1)
		cmd->io_out = open((*toks)->content, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (len == 2)
	{
		cmd->io_out = open((*toks)->content, O_RDWR | O_APPEND | O_CREAT, 0666);
		cmd->dgreat = TRUE;
	}
	if (cmd->io_out == -1)
	{
        printf("%s : %s \n", cmd->cmd_args[0], strerror(errno));
		cmd->error = TRUE;
	}
}

void redirect_in(t_cmd *cmd, t_token **toks, int len)
{
	if (len == 1)
		cmd->io_in = open((*toks)->content, O_RDWR | O_TRUNC, 0666);
	if (len == 2)
	{
		if (!cmd->io_here)
			cmd->io_here = malloc(sizeof(char *) * (cmd->here_words + 2));
		else
			cmd->io_here = (char **)ft_realloc_double_pointer((void **)cmd->io_here, sizeof(char *) * ((cmd->here_words - 1) + 2),
				sizeof(char *) * (cmd->here_words + 2)); //realloc a double tab
		cmd->io_here[cmd->here_words] = ft_strdup((*toks)->content);
		cmd->io_here[cmd->here_words + 1] = NULL;
		cmd->here_words += 1;
		cmd->dless = TRUE;
	}
	if (cmd->io_in == -1)
	{
        printf("%s : %s \n", cmd->cmd_args[0], strerror(errno));
		cmd->error = TRUE;
	}
}

void redirect(t_cmd *cmd, t_token **toks, int type, int len)
{
	if (!(*toks)->next)
		return ((void)0);
	*toks = (*toks)->next;
	if (type == TOK_LESS)
		redirect_in(cmd, toks, len);
	else if (type == TOK_GREAT)
		redirect_out(cmd, toks, len);
}
