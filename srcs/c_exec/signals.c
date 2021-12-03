/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:57:16 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/02 16:11:46 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler_main(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	printf(BWHT"Minishell "BRED"> "RESET);
	g_return_value = 130;
}

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_return_value = 130;
	printf("\n");
}

/*
**	my_getc overrides default function rl_getc that
**	ignores signals
**	Reads character by character and
*/

int	my_getc(FILE *stream)
{
	int		r;
	char	c;

	(void)stream;
	r = read(0, &c, 1);
	if (r == -1)
		return (EOF);
	else
		return (c);
}

void	ignore_other_sig(void)
{
	int	i;

	i = 0;
	while (++i <= 31)
	{
		if (i != SIGINT && i != SIGQUIT
			&& i != SIGCHLD && i != SIGPIPE
			&& i != SIGKILL && i != SIGSTOP)
			signal(i, SIG_IGN);
	}
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
	ignore_other_sig();
	if (state == MAIN_PROCESS)
	{
		signal(SIGINT, sigint_handler_main);
		signal(SIGQUIT, SIG_IGN);
	}
	if (state == HEREDOC)
	{
		rl_getc_function = my_getc;
		signal(SIGINT, sigint_handler_heredoc);
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
