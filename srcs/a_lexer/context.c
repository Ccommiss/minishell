/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:58:45 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/05 21:07:31 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	These functions, called according to the context, return a token
**	defining how to interpret the current char given the context.
**	Ex. while lexing a word, a ' ' should be interpreted as a stop
**	character, while not if in a quoted context.
*/

enum	e_tokens	op_toks(int c)
{
	static enum e_tokens	tok[256] = {
	['|'] = TOK_PIPE,
	['<'] = TOK_LESS,
	['>'] = TOK_GREAT,
	['='] = TOK_EQUAL
	};

	return (tok[c]);
}

/*
**	word toks : in WORD context, pipes, less, great
**	and spaces are interpreted as non word tokens.
*/

enum	e_tokens	word_toks(int c)
{
	static enum e_tokens	tok[256] = {
	['\0'...' '] = TOK_EAT, // CARACTERES D'ARRET
	['#'...'&'] = TOK_WORD, // 35 a 38
	['('...'/'] = TOK_WORD, //40 a 47
	['0'...'9'] = TOK_WORD, //48 a 57
	[':'...';'] = TOK_WORD,
	['='] = TOK_WORD,
	['?'...'@'] = TOK_WORD, // 58 a 59 et 61, 63, 64
	['A'...'z'] = TOK_WORD, //97 a 122
	['{'] = TOK_WORD,
	['}'] = TOK_WORD, //123,125
	['~'...u'ÿ'] = TOK_WORD, // 126 a la fin
	['|'] = TOK_PIPE,
	['<'] = TOK_LESS,
	['>'] = TOK_GREAT,
	['\''] = TOK_WORD, //39
	['\"'] = TOK_WORD, //34
	};

	return (tok[c]);
}

/*
**	expand toks : in VAR context, all chars but all types of
**	spaces are considered as word token.
*/

enum	e_tokens	expand_toks(int c)
{
	static enum e_tokens	tok[256] = {
	['\0'...' '] = TOK_EAT,
	['\"'...u'ÿ'] = TOK_WORD
	};

	return (tok[c]);
}

enum e_tokens	tok(int x, int y)
{
	if (x == OP)
		return (op_toks(y));
	if (x == WORD)
		return (word_toks(y));
	if (x == SQUOTE || x == DQUOTE)
		return (TOK_WORD);
	if (x == VAR)
		return (expand_toks(y));
	return (WORD);
}

/*
**	Memo ASCII
**
**	0 a 32 : non-printable characters
**	33 ... 47 : ponctuation
**		├─> 34 : "
**		├─> 36 : $
**		├─> 39 : '
**	48 a 57 : chiffres
**	58 a 64 : operateurs
**		├─> 60 : <
**		├─> 62 : >
**	65 a 90 : A a Z
**	91 a 96 : ponctuation '[' a '`'
**	97 a 122 : a a z
**	123 a 127 : ponctuation { a ~ puis DEL
**	128 a 254 : Ascii extended
*/

/*
**	corresp : defines the reference character of
**	the current examind sequence of char.
*/

enum e_tokens	corresp(int c)
{
	static enum e_tokens	corresp[256] = {
	['|'] = OP,
	['<'] = OP,
	['>'] = OP,
	['\0'...'!'] = WORD,
	['#'...'&'] = WORD,
	['('...'/'] = WORD,
	['0'...'9'] = WORD,
	[':'...';'] = WORD,
	['='] = WORD,
	['?'...'@'] = WORD,
	['A'...'Z'] = WORD,
	['['...'`'] = WORD,
	['a'...'z'] = WORD,
	['{'] = WORD,
	['}'] = WORD,
	['~'...u'ÿ'] = WORD,
	['\''] = SQUOTE,
	['\"'] = DQUOTE,
	};

	return (corresp[c]);
}
