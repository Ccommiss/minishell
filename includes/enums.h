#ifndef ENUMS_H
# define ENUMS_H


enum booleen
{
	ERROR = -1,
	BREAK = -1,
	FALSE,
	TRUE,
	MALLOC_FAIL = -100
};

enum io {
	NOT_SPECIFIED = -100
};

enum signal_location
{
	MAIN_PROCESS,
	CHILD,
	CHILD_HANDLING,
	HEREDOC
};

enum expand
{
	NO_BRACE,
	OPEN_BRACE = 1,
	CLOSE_BRACE = 2,
	DOL_OR_QUEST = 3,
	BAD_SUBSTIT = 4
};


/*
**	Enum mainly used in lexing for context purposes
**
**	Nb. we need to differentiate :
**		- TOK_ERR : meaning a bad substitution error, that prevents
**			the current cmd to be executed
**		- TOK_NO_VAR : meaning a $ that did not match any key in env,
**			resulting in NULL
**		- SYNT_ERR : syntax error preventing the whole cmd line to be executed
*/
enum tokens
{
	OP = 4,
	WORD = 1,
	QUOTE = 2,
	VAR = 3,
	TOK_EAT = 404,
	TOK_WORD = 100,
	TOK_PIPE,
	TOK_GREAT,
	TOK_LESS,
	TOK_EQUAL,
	TOK_ERR,
	TOK_NO_VAR,
	SYNT_ERR,
	SQUOTE = '\'',
	DQUOTE = '\"'
};

#endif
