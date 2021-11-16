#include "minishell.h"


void intHandler()
{
    rl_reset_line_state();
    printf("\n");
    rl_replace_line("", 0);
}

void intHandlerMain()
{
	g_utils.return_value = 130;
    printf("\n");
    rl_replace_line("", 0);
	rl_redisplay();
	printf(BWHT"Minishell "BRED"> "RESET);
}

// on va faire commencer les signaux a
// 100 ; 100 equivaudra a 0 dans les [heree doc word] etc,
// 101 a 1, etc.


void intHandler_heredoc()
{
    g_utils.g_sig = 1;
	g_utils.return_value = 130;
     //rl_reset_line_state();

     // rl_insert_text("wow  je suis la");
      rl_done = 1;
     // rl_line_buffer = NULL;
     // printf("\n");

      //close(".here_doc");
      //rl_on_new_line ();

      //rl_pending_input = 'i';

     // rl_on_new_line ();
    // rl_redisplay();

    return ;

    //rl_replace_line("", 0);
	printf ("%s", BWHT"WOW Minishell "BRED"> "RESET);
}

void 	quithandler()
{
	printf ("Quit (core dumped)");
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
	if (state == HEREDOC)
	{
		signal(SIGINT, intHandler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
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
