#include "minishell.h"

void intHandlerMain()
{
	return_value = 130;
    printf("\n");
  	rl_replace_line("", 0);
	rl_redisplay();
	printf(BWHT"Minishell "BRED"> "RESET);
}

void intHandler_heredoc()
{
	return_value = 130;
    printf("\n");
    return ;
}

/*
**	
*/

static int my_getc(FILE *stream)
{
 (void)stream;
   int r;
   char c;

    r = read(0, &c, 1); // read from stdin, will return -1 when interrupted by a signal
    if (r == -1)// && errno == EINTR)
        return EOF;
    else
        return c;
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
	rl_getc_function = rl_getc;

    if (state == MAIN_PROCESS)
    {
	    signal(SIGINT, intHandlerMain);
	    signal(SIGQUIT, SIG_IGN);
    }
	if (state == HEREDOC)
	{
        rl_getc_function = my_getc;
		signal(SIGINT, intHandler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
    if (state == CHILD)
    {
        signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
    }
    if (state == CHILD_HANDLING)
    {
       signal(SIGQUIT, SIG_IGN);
       signal(SIGINT, SIG_IGN);
    }

}
