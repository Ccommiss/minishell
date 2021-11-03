#include "minishell.h"

/*
**	These functions, called according to the contexte, return a token
**	defining how to interpret the current char given the context.
**	Ex. while lexing a word, a ' ' should be interpreted as a stop
**	character, while not if in a quoted context.
*/

enum	tokens	op_toks(int c)
{
	static enum tokens	tok[256] = {
			['|'] = TOK_PIPE,
			['<'] = TOK_LESS,
			['>'] = TOK_GREAT,
			['='] = TOK_EQUAL
	};

	return (tok[c]);
}

enum	tokens	word_toks(int c)
{
	static enum tokens	tok[256] = {
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

enum	tokens	quote_toks(int c)
{
	static enum tokens	tok[256] = {
		['\0'...u'ÿ'] = TOK_WORD
	};

	return (tok[c]);
}
