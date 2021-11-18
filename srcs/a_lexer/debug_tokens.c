#include "minishell.h"


static char *tokentype[1000] = {
	[TOK_PIPE] = "PIPE",
	[TOK_WORD] = "WORD",
	[TOK_LESS] = "LESS",
	[TOK_GREAT] = "GREAT",
	[TOK_EQUAL] = "EQUAL",
	[SYNT_ERR] = "SYNTAX ERR",
	[TOK_ERR] = "EXPAND ERR"
};

void	debug_tokens(t_token *toks)
{


	printf (BCYN"\n\n 			--- DEBUG TOKEN ---\n\n"RESET);
	printf("-------------------------------------------------------------------\n");
	printf("| INDEX | TYPE       | LEN | CONTENT                               |\n");
	printf("|-------|------------|-----|---------------------------------------|\n");
	while (toks != NULL && toks->content != NULL)
	{
		printf("| %2d    ", toks->index);

		if (toks->type == SYNT_ERR)
			printf(BWHT"| "BRED"%10s ", tokentype[toks->type]);
		else if (toks->type == TOK_LESS || toks->type == TOK_PIPE || toks->type == TOK_GREAT)
			printf(BWHT"| "BYEL"%10s ", tokentype[toks->type]);
		else
			printf(BWHT"| %10s ", tokentype[toks->type]);
		printf(BWHT"| %3d ", toks->len);
		printf(BWHT"|		|%s|\n"RESET, toks->content);
		printf("|------------------------------------------------------------------|\n");
		toks = toks->next;
	}

}
