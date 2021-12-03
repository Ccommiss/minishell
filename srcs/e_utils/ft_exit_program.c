#include "minishell.h"

void	ft_exit_program(t_cmd *cmd, t_token *toks, char *str, void *stuff)
{
	(void)stuff;
	cleanup(cmd, toks, str);
	if (stuff)
		free(stuff);
	exit(1);
}
