#include "minishell.h"

void	redirect_out(t_cmd *cmd, t_token **toks, int len)
{
	if (len == 1)
	{
		cmd->io_out = open((*toks)->content, O_RDWR | O_TRUNC | O_CREAT, 0666);
	}
	if (len == 2)
	{
		cmd->io_out = open((*toks)->content, O_RDWR | O_APPEND | O_CREAT, 0666);
		cmd->dgreat = TRUE;
	}
	else if (len > 2)
	{
		printf ("minishell : syntax error near unexpected token\n");
		cmd->error = TRUE;
	}
	if (cmd->io_out == -1)
		printf("%s : %s \n", cmd->cmd_args[0], strerror(errno));
}

void	redirect_in(t_cmd *cmd, t_token **toks, int len)
{
	if (len == 1)
		cmd->io_in = open((*toks)->content, O_RDWR, 0666);
	if (len == 2)
	{
		if (!cmd->io_here)
			cmd->io_here = malloc(sizeof(char *) * (cmd->here_words + 2));
		else
			cmd->io_here = ft_realloc(cmd->io_here, sizeof(char *) * (cmd->here_words + 1),
			sizeof(char *) * (cmd->here_words + 2));
		cmd->io_here[cmd->here_words] = ft_strdup((*toks)->content);
		cmd->io_here[cmd->here_words + 1] = NULL;
		cmd->here_words += 1;
		cmd->dless = TRUE;
	}
	if (cmd->io_in == -1 && cmd->dless == FALSE)
		printf("%s : %s \n", cmd->cmd_args[0], strerror(errno));
}

void	redirect(t_cmd *cmd, t_token **toks, int type, int len)
{
	if (!(*toks)->next)
		return ((void)0);
	*toks = (*toks)->next;
	if (type == TOK_LESS)
		redirect_in(cmd, toks, len);
	else if (type == TOK_GREAT)
		redirect_out(cmd, toks, len);
}
