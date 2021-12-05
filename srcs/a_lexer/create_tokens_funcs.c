/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:34:38 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/05 21:17:29 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	create toks : creates token from the current lex struct
**	data made in tokenize function
*/

void	create_token(t_token **toks, t_lex *l)
{
	if ((*toks)->index == -1)
		(*toks)->index = 0;
	if ((*toks)->content == NULL && l->ref_char != TOK_NO_VAR)
		(*toks)->content = ft_strdup(l->token);
	else
		(*toks)->content = NULL;
	(*toks)->type = l->ref_char;
	if ((*toks)->content)
		(*toks)->len = ft_strlen((*toks)->content);
	else
		(*toks)->len = -1;
	syntax_error_detector(*toks, FALSE);
	(*toks)->next = malloc(sizeof(t_token));
	(*toks)->next->content = NULL;
	(*toks)->next->prev = (*toks);
	(*toks)->next->index = (*toks)->index + 1;
	(*toks) = (*toks)->next;
}

/*
**	creates toks : creates a token labelled as ERR which means
**	we had an error during the substitution.
**	Iterates until finding a pipe to make
**	the next token, or the end of the input.
*/

int	create_exp_err_token(char **to_tokenize, int *i, t_lex *l)
{
	l->ref_char = TOK_ERR;
	ft_bzero(l->token, 2048);
	while (to_tokenize[0][*i] && to_tokenize[0][*i] != '|')
		*i += 1;
	return (ERROR);
}
