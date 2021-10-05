#include "minishell.h"


static char *tokentype[1000] = {
	[TOK_PIPE] = "PIPE",
	[TOK_WORD] = "WORD",
	[TOK_LESS] = "LESS",
	[TOK_GREAT] = "GREAT",
	[TOK_EQUAL] = "EQUAL"
};

void	debug_tokens(t_token *toks)
{


	printf (BCYN"\n\n 			--- DEBUG TOKEN ---\n\n"RESET);
	printf("-------------------------------------------------------------------\n");
	printf("| INDEX | TYPE   | LEN | CONTENT                                   |\n");
	printf("|-------|--------|-----|-------------------------------------------|\n");
	while (toks != NULL)
	{
		printf("| %2d    ", toks->index);
		printf(BWHT"| %6s ", tokentype[toks->type]);
		printf(BWHT"| %3d ", toks->len);
		printf(BWHT"|		|%s|\n"RESET, toks->content);
		printf("|------------------------------------------------------------------|\n");
		toks = toks->next;
	}

}
