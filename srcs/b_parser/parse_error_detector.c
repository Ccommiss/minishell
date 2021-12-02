/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_detector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:01:19 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/02 16:01:20 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_items(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd_args)
	{
		while (cmd->cmd_args[i])
			free(cmd->cmd_args[i++]);
		free(cmd->cmd_args);
		cmd->cmd_args = NULL;
	}
	if (cmd->cmdp)
		free(cmd->cmdp);
}

/*
**  syn_err_or_no_tok returns error if errors are found
**	- Call to check syn error : sends the whole packet of
**		toks and iterates through them to find if an error
**		is detected before pointing back on head
**		(that's why we only check once when we are on 0 index)
**	- If no toks are found (tok->index = -1)
**
**	If error is returned, NOT ANY COMMAND is made, all the
**	current line is canceled.
*/

int	syn_err_or_no_tok(t_cmd *cmd, t_token *toks)
{
	if (toks->index == -1)
		return (ERROR);
	if (toks->index == 0 && check_syn_err(toks) == ERROR)
	{
		cmd->error = 1;
		free_command_items(cmd);
		free_toks(toks);
		return (ERROR);
	}
	return (1);
}

/*
**	Check syn err checks if
**	- one token contains a syntax error (if <<< for exemple)
**	- if only empty tokens were found
*/
int	check_syn_err(t_token *toks)
{
	t_token	*head;
	int		error;
	int		max_len;

	head = toks;
	error = 0;
	max_len = -1;
	while (toks)
	{
		max_len = toks->len;
		if (toks->type == SYNT_ERR)
			error = TRUE;
		toks = toks->next;
	}
	if (error || max_len == -1)
		return (ERROR);
	toks = head;
	return (TRUE);
}
