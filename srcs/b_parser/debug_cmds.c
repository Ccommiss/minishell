#include "minishell.h"


void	debug_cmds(t_cmd *cmds)
{
	printf (BCYN"\n\n 			--- COMMAND TABLE ---\n\n"RESET);

	while (cmds != NULL)
	{
		printf(MAG"[%2d]\n"RESET, cmds->index);
		printf(BWHT"├─ Command\n"RESET);
		printf("│  ├─ %6s\n", cmds->cmd_args[0]);
		printf(BWHT"├─ Command suffixs\n"RESET);
		int i = 0;
		while (cmds->cmd_args[i])
			printf ("│  ├─ %s\n", cmds->cmd_args[i++]);
		printf(BWHT"├─ Redirections\n"RESET);
		printf("│  ├─> in (<) : %d\n", cmds->io_in);
		printf("│  │   ├─> dless : %d\n", cmds->dless);
		printf("│  ├─> out (>): %d\n", cmds->io_out);
		printf("│  │   ├─> dgreat : %d\n", cmds->dgreat);
		printf("|------------------------------------------------------------------|\n");
		cmds = cmds->next;
	}
}
