/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:59:03 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/05 20:45:08 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		Init lexer struct is called each time to_tokenize resend
**		itself into the tokenize function.
**		It holds all data related to the current token being made.
**		· Lex->ref char : designs the 'reference character', which
**			is the type of the first character
**		· Lex->context : by default, this is WORD, unless we are on
**			a VAR context. It will be changed further in quotes
**			and expand handling functions.
**			(if VAR, operators should be interpreted as TOK_WORDS
**			which differs from WORD context)
**
*/

void	init_lexer_struct(t_lex *lex, char *to_tokenize, int save_exp)
{
	ft_bzero(lex->token, 2048);
	lex->buf_i = 0;
	lex->ref_char = tok(corresp((unsigned char)to_tokenize[0]),
			(unsigned char)to_tokenize[0]);
	lex->context = WORD;
	lex->exp_res = -2;
	lex->exp_len = save_exp;
	if (lex->exp_len > 0 && lex->ref_char != TOK_EAT)
	{
		lex->context = VAR;
		lex->ref_char = TOK_WORD;
	}
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
