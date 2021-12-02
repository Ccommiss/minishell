#include "minishell.h"

void	redirect_out(t_cmd *cmd, t_token **toks, int len)
{
	if (len == 1 && cmd->error == FALSE)
	{
		if (cmd->io_out > 0)
			close(cmd->io_out);
		cmd->io_out = open((*toks)->content, O_RDWR | O_TRUNC | O_CREAT, 0666);
	}
	if (len == 2 && cmd->error == FALSE)
	{
		cmd->io_out = open((*toks)->content, O_RDWR | O_APPEND | O_CREAT, 0666);
		cmd->dgreat = TRUE;
	}
	if (cmd->io_out == -1)
	{
		if (cmd->error == FALSE)
			ft_print_error(cmd->cmd_args[0]);
		cmd->error = TRUE;
		return_value = 1;
	}
}

void	set_heredoc(t_cmd *cmd, t_token **toks)
{
		if (!cmd->io_here)
			cmd->io_here = malloc(sizeof(char *) * (cmd->here_words + 2));
		else
			cmd->io_here = ft_realloc(cmd->io_here, sizeof(char *)
					* (cmd->here_words + 1), sizeof(char *)
					* (cmd->here_words + 2));
		cmd->io_here[cmd->here_words] = ft_strdup((*toks)->content);
		cmd->io_here[cmd->here_words + 1] = NULL;
		cmd->here_words += 1;
		cmd->dless = TRUE;

}

void	redirect_in(t_cmd *cmd, t_token **toks, int len)
{
	if (len == 1 && cmd->error == FALSE)
	{
		if (cmd->io_in > 0)
			close(cmd->io_in);
		cmd->io_in = open((*toks)->content, O_RDWR, 0666);
	}
	if (len == 2)
	{
		set_heredoc(cmd, toks);
	}
	if (cmd->io_in == -1 && cmd->dless == FALSE)
	{
		if (cmd->error == FALSE)
			ft_print_error((*toks)->content);
		cmd->error = TRUE;
		return_value = 1;
	}
}

/*
**	redirect choose whether
** 	- returning an lexical error if token < or > is not followed by
**		a file name
**	- redirect in
**	- redirect out
*/
void	redirect(t_cmd *cmd, t_token **toks, int type, int len)
{
	if (!(*toks)->next)
		return ((void)0);
	*toks = (*toks)->next;
	if (type == TOK_LESS)// && cmd->error == FALSE)
		redirect_in(cmd, toks, len);
	else if (type == TOK_GREAT)// && cmd->error == FALSE)
		redirect_out(cmd, toks, len);
}
