#include "minishell.h"


void intHandler()
{
    rl_reset_line_state();
    printf("\n");
    rl_replace_line("", 0);
}

void intHandlerMain()
{
    rl_reset_line_state ();
    printf("\n");
    rl_replace_line("", 0);
	rl_redisplay();
}

void 	quithandler()
{
	printf ("Core Dumped\n");
	rl_reset_line_state ();
	printf("\n");
	rl_replace_line("", 0);
}


/*
**  Handles signal according to the current situation
**
**  1) MAIN PROCESS : while prompt in interactive mode, 
**          ignores ctrl \, and displays ^C + a newline
**  2) CHILD : when child process is created, just before
**      executing, restores default signal handling (SIG_DFL)
**      so that command is effectively killed 
**  3) CHILD_HANDLING : after forking, when in the parent, 
**      prompts "core dump" as in Linux after the command 
**      was killed   
*/

void	handle_signal(int state)
{
    if (state == MAIN_PROCESS)
    {
	    signal(SIGINT, intHandlerMain);
	    signal(SIGQUIT, SIG_IGN);
    }
    else if (state == CHILD)
    {
        signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
    }
    else if (state == CHILD_HANDLING)
    {
       signal(SIGQUIT, quithandler);
       signal(SIGINT, intHandler);
    }
}
