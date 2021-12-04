/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:59:57 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/04 09:35:32 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	same_token(unsigned char tested_c, t_lex *l, int old_context)
{
	if (l->ref_char == (int)tok(old_context, tested_c))
		return (TRUE);
	else if (l->context == VAR && l->ref_char == (int)tok(VAR, tested_c))
		return (TRUE);
	return (FALSE);
}

/*
** 	After expands, reset the original context (eg. dquotes or word)
**	(cause $a or "$a" if $a = ls -la wont be interpreted the same)
*/
void	save_and_reset_context(int	*old_context, t_lex **l)
{
	if (*old_context == -1)
	{
		*old_context = (*l)->context;
		return ;
	}
	if ((*l)->context == VAR && (*l)->exp_len == 0)
		(*l)->context = *old_context;
	else if ((*l)->context != VAR)
		*old_context = (*l)->context;
}

int	fill_token_buff(t_lex *l, char **to_tokenize, int *i, t_env *env)
{
	int			protect;
	static int	old_context = -1;

	protect = 0;
	save_and_reset_context(&old_context, &l);
	while (to_tokenize[0][*i]
		&& same_token((unsigned char)to_tokenize[0][*i], l, old_context))
	{
		save_and_reset_context(&old_context, &l);
		handle_quoted_context(&(l->context), i, *to_tokenize);
		save_and_reset_context(&old_context, &l);
		protect = handle_expand(to_tokenize, i, l, env);
		if (protect == MALLOC_FAIL)
			return (MALLOC_FAIL);
		else if (protect == -1)
			break ;
		l->token[l->buf_i++] = to_tokenize[0][*i];
		if (to_tokenize[0][*i])
			*i += 1;
		if (l->exp_len > 0)
			l->exp_len--;
	}
	l->token[l->buf_i] = '\0';
	l->buf_i = 0;
	return (0);
}

void	rewind_toks(t_token *toks)
{
	toks = toks->prev;
	free(toks->next);
	toks->next = NULL;
	if (error_tab(toks->type) == OP)
		syntax_error_detector(toks, TRUE);
}

/*
**	tokenize : recursive function that builds a chained list of tokens
**
**	It compares the interpretation of the first char (l.ref_char)
**	with interpretation of next char (to_tokenize[i])
**	@param to_tokenize : chaine de commande
**	@t_token
*/
void	tokenize(char *line, t_token *toks, t_env *env)
{
	t_lex		l;
	int			i;
	char		*to_tokenize;
	static int	save_exp = 0;

	i = 0;
	to_tokenize = ft_strdup(line);
	if (!to_tokenize)
		ft_exit_program(NULL, toks, line, NULL);
	init_lexer_struct(&l, to_tokenize, save_exp);
	if (fill_token_buff(&l, &to_tokenize, &i, env) == MALLOC_FAIL)
		ft_exit_program(NULL, toks, line, NULL);
	save_exp = l.exp_len;
	if (l.ref_char != TOK_EAT)
		create_token(&toks, &l);
	to_tokenize = ft_auto_substr(to_tokenize, i, ft_strlen(to_tokenize));
	if (!to_tokenize)
		ft_exit_program(NULL, toks, line, NULL);
	if (to_tokenize && ft_strlen(to_tokenize) != 0)
		tokenize(to_tokenize, toks, env);
	else if (toks && toks->prev)
		rewind_toks(toks);
	free (to_tokenize);
	to_tokenize = NULL;
}
