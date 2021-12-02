/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:34:38 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/03 00:34:40 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	create_exp_err_token(char **to_tokenize, int *i, t_lex *l)
{
	l->ref_char = TOK_ERR;
	ft_bzero(l->token, 2048);
	while (to_tokenize[0][*i] && to_tokenize[0][*i] != '|')
		*i += 1;
	return (ERROR);
}
