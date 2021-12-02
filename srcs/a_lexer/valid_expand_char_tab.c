#include "minishell.h"

/*
** is_valid_expand_char test each of character to know if
**	1 - We are still in the expand context (no space) or
**		no followed by another var (another $var)
**	2 - In case of braces, if no 'bad substitution char'
**		is found inside
*/

int	is_valid_expand_char(int *exception, int c, int j)
{
	static int	valid_tab[4][256] = {
	[NO_BRACE]['A'...'Z'] = 1,
	[NO_BRACE]['a'...'z'] = 1,
	[NO_BRACE]['1'...'9'] = 1,
	[NO_BRACE]['{'] = 1,
	[OPEN_BRACE]['\0'...u'ÿ'] = 1,
	[CLOSE_BRACE]['}'] = 1,
	[DOL_OR_QUEST]['?'] = 1,
	[DOL_OR_QUEST]['$'] = 1,
	};
	static int	set_exception[4][256] = {
	[NO_BRACE]['?'] = DOL_OR_QUEST,
	[NO_BRACE]['$'] = DOL_OR_QUEST,
	[NO_BRACE]['{'] = OPEN_BRACE,
	[OPEN_BRACE]['}'] = CLOSE_BRACE,
	[OPEN_BRACE]['$'] = DOL_OR_QUEST,
	[DOL_OR_QUEST]['$'] = NO_BRACE,
	[DOL_OR_QUEST]['}'] = CLOSE_BRACE,
	};

	if (j == 1 || c == '}' || (j > 1 && *exception == DOL_OR_QUEST))
		*exception = set_exception[*exception][c];
	return (valid_tab[*exception][c]);
}
