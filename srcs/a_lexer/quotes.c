#include "minishell.h"

void	handle_quoted_context(int *context, int *i, char *to_tokenize)
{
	if (!to_tokenize[*i]) // test
		return ;
	//printf ("{handle quote} to_tokenize[%d] = %c \n", *i, to_tokenize[*i]);
	if (*context != DQUOTE && *context != SQUOTE
		&& (to_tokenize[*i] == SQUOTE  && ft_strchr(to_tokenize + *i +1, SQUOTE)))
	{
		*i += 1;
		*context = SQUOTE;
	}
	else if (*context != SQUOTE && *context != DQUOTE
		&& (to_tokenize[*i] == DQUOTE && ft_strchr(to_tokenize + *i +1, DQUOTE)))
	{
		*i += 1;
		*context = DQUOTE;
	}
	else if ((*context == SQUOTE && to_tokenize[*i] == SQUOTE)
		|| (*context == DQUOTE && to_tokenize[*i] == DQUOTE))
	{
		*i += 1;
		*context = WORD;
	}
	if (((int)to_tokenize[*i] == SQUOTE && *context != DQUOTE)
		|| ((int)to_tokenize[*i] == DQUOTE && *context != SQUOTE)) // test pour gerer si "" collees
		handle_quoted_context(context, i, to_tokenize);
}
