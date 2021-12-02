#include "minishell.h"

void	init_lexer_struct(t_lex *lex, char *to_tokenize)
{
	ft_bzero(lex->token, 2048);
	lex->buf_i = 0;
	lex->ref_char = tok(corresp((unsigned char)to_tokenize[0]),
			(unsigned char)to_tokenize[0]);
	lex->context = corresp((unsigned char)to_tokenize[0]);
	if (lex->context == SQUOTE || lex->context == DQUOTE)
		lex->context = WORD;
	lex->exp_res = -2;
	lex->exp_len = 0;
}

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