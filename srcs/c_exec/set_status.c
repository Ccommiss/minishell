#include "minishell.h"

void set_status(int status)
{
	//printf("|   %-20s|   %-20s|   %-20s|   %-20s|\n", "STATUS", "WIFEXITED STATUS", "WEXITEDSTATUS", "WIFSIGNAL");
	//printf("|   %-20d|   %-20d|   %-20d|   %-20d|\n", status, WIFEXITED(status), WEXITSTATUS(status), WIFSIGNALED(status));

	if (WIFSIGNALED(status) == 1) // interrompu par signal
	{
		printf("YOYOOYOY INTERRUPTION \n");
		if (status < 128)
			status = 128 + status; //sur Mac en tt cas
		return_value = status;
		if (return_value == 131)
			printf ("Quit (core dumped)\n");
		if (return_value == 130)
			printf ("\n");
	}
	else if (WIFEXITED(status) == 1) // fils interrompu normalement par un exit
		return_value = WEXITSTATUS(status);
}
