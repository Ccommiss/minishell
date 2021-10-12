#include "minishell.h"


char *interpret(int num)
{
	//char unspecified[] = "Redirection not specified\n";
	if (num == -1)
		return ("-1");
	if (num == NOT_SPECIFIED)
		return ("Redirection not specified");
	else
		return (ft_itoa(num)); //itoa ne fonctionne aps avec negatifs?? ? 
}

void	debug_cmds(t_cmd *cmds)
{
	printf (BCYN"\n\n 			--- COMMAND TABLE ---\n\n"RESET);

	while (cmds != NULL)
	{
		printf(MAG"[%2d]\n"RESET, cmds->index);
		printf(BWHT"├─ Command\n"RESET);
		if (cmds->cmd_args)
		printf("│  ├─ %-6s\n", cmds->cmd_args[0]);
		printf("│  ├─ [path] %6s\n", cmds->cmdp);
		printf(BWHT"├─ Command suffixs\n"RESET);
		int i = 0;
		while (cmds->cmd_args[i])
			printf ("│  ├─ %s\n", cmds->cmd_args[i++]);
		printf(BWHT"├─ Redirections\n"RESET);
		printf("│  ├─> in (<) : %s\n", interpret(cmds->io_in));
		printf("│  │   ├─> dless : %d\n", cmds->dless);
		printf("│  │   ├─> heredoc : %s\n", cmds->io_here);
		printf("│  ├─> out (>): %s\n", interpret(cmds->io_out));
		printf("│  │   ├─> dgreat : %d\n", cmds->dgreat);
		printf("|------------------------------------------------------------------|\n");
		cmds = cmds->next;
	}
}
