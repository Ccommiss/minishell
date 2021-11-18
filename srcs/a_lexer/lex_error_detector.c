#include "minishell.h"

enum tokens	error_tab(int type)
{
	static enum tokens	op_table[256] = {
		[TOK_GREAT] = OP,
		[TOK_LESS] = OP,
		[TOK_PIPE] = OP
	};

	return (op_table[type]);
}

/*
**	syntax_error_detector handles :
**	- if more than expected operators are found (ex. <<<, ||, etc)
**	- if operators are doubled (ex echo lol > >> file), e.g.
**		not preceded by a TOK_WORD token
** 	- reste a gerer -> si TOK en fin de ligne 
**   - NEXT TOK IS ALWAYS NULL as this function is called in each tok
*/
void	syntax_error_detector(t_token *toks)
{
	char	tok_op;

	if (toks->type == TOK_GREAT)
		tok_op = '>';
	if (toks->type == TOK_LESS)
		tok_op = '<';
	if (toks->type == TOK_PIPE)
		tok_op = '|';
	if (((toks->type == TOK_GREAT || toks->type == TOK_LESS) && toks->len > 2) // si <<< ou >>> 
		|| (toks->type == TOK_PIPE && toks->len > 1) // si || 
		|| ((toks->type == TOK_PIPE && !toks->prev)// || toks->prev->type != TOK_ERR || toks->prev->type != TOK_WORD)) //
		|| (toks->prev && error_tab(toks->type) == OP && error_tab(toks->prev->type) == OP)))
	{
		toks->type = SYNT_ERR;
		//if (return_value != 2)
			printf("minishell : syntax error near \"%c\"\n", tok_op);
		return_value = 2;
	}
}

/*
** 	Expand finds the var name to tokenize in the user input and send it
**	to be replaced.
*/

int	expand_substitution_error_detector(char *var_name, int exception)
{
	char	*trimmed_var;

	if (exception == OPEN_BRACE)
	{
		printf("%s : brace error, please close them\n", var_name);
		free(var_name);
		return (ERROR);
	}
	if (exception == CLOSE_BRACE)
		trimmed_var = ft_substr(var_name, 2, ft_strlen(var_name) - 3);
	else
		trimmed_var = ft_substr(var_name, 1, ft_strlen(var_name) - 1);
	if (!ft_isalnum_str(trimmed_var)
		&& ft_strncmp(trimmed_var, "?", 2) != 0
		&& ft_strncmp(trimmed_var, "$", 2) != 0)
	{
		printf("%s : bad substitution\n", var_name);
		return_value = 1;
		free(var_name);
		return (ERROR);
	}
	free(trimmed_var);
	free(var_name);
	return (0);
}
