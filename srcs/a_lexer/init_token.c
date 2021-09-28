#include "../../include/minishell.h"

void	init_token(t_token *toks)
{
	toks->index = 0;
	toks->content = NULL;
	toks->len = -1;
	toks->type = -1;
	toks->prev = NULL;
	toks->next = NULL;

}
