#include "minishell.h"

void	syntax_error_detector(t_token *toks)
{
	char	tok_op;

	if (toks->type == TOK_GREAT)
		tok_op = '>';
	if (toks->type == TOK_LESS)
		tok_op = '<';
	if (toks->type == TOK_PIPE)
		tok_op = '|';
	if (((toks->type == TOK_GREAT || toks->type == TOK_LESS) && toks->len > 2)
		|| (toks->type == TOK_PIPE && toks->len > 1))
	{
		toks->type = SYNT_ERR;
		if (return_value != 2)
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
