#include "minishell.h"

/*
**	handle_quoted_context modifies context
**	- if the context is not double quote, neither simple quote,
**		 but the current char is " -> context set to double quote
**		 but the current char is ' -> 				 simple quote
**	- if we are closing the current quotes, context go back to WORD
**
**	This function is recursive if we are encountering sticked quotes
**	like "WORD""OTHERWORD"
*/
void	handle_quoted_context(int *context, int *i, char *to_tokenize)
{
	if (!to_tokenize[*i])
		return ;
	if (*context != DQUOTE && *context != SQUOTE
		&& (to_tokenize[*i] == SQUOTE)
		&& ft_strchr(to_tokenize + *i + 1, SQUOTE))
	{
		*i += 1;
		*context = SQUOTE;
	}
	else if (*context != SQUOTE && *context != DQUOTE
		&& (to_tokenize[*i] == DQUOTE)
		&& ft_strchr(to_tokenize + *i + 1, DQUOTE))
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
		|| ((int)to_tokenize[*i] == DQUOTE && *context != SQUOTE))
		handle_quoted_context(context, i, to_tokenize);
}