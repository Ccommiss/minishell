/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:00:40 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/02 21:44:15 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create next command will create the next command
**	and set the current toks to next if it is a pipe
*/

void	create_next_command(t_cmd **cmd, t_token **toks)
{
	(*cmd)->next = malloc(sizeof(t_cmd));
	if (!(*cmd)->next)
		ft_exit_program((*cmd), (*toks), NULL, NULL);
	(*cmd)->next->prev = *cmd;
	if ((*toks)->type == TOK_PIPE)
		(*toks) = (*toks)->next;
	token_to_cmds((*cmd)->next, (*toks));
}

/*
**	Set error to the current cmd when a
** 	TOK_ERR (= a bad substitution) is encountered.
**
**	It then iterates through tokens without analyse
**	until next command (if so).
**
**	Nexts commands are made.
*/

int	set_error(t_cmd *cmd, t_token **toks)
{
	if ((*toks)->type != TOK_ERR)
		return (0);
	cmd->error = TRUE;
	while ((*toks) && (*toks)->type != TOK_PIPE)
		(*toks) = (*toks)->next;
	return (1);
}

void	token_to_cmds(t_cmd *cmd, t_token *toks)
{
	int		j;
	t_token	*head;

	j = 0;
	head = toks;
	if (syn_err_or_no_tok(cmd, toks) == ERROR)
		return ;
	printf ("INIT \n");
	init_cmd (cmd);
	while (toks && toks->type != TOK_PIPE)
	{
		if (toks->type == TOK_ERR && set_error(cmd, &toks) == 1)
			break ;
		if (toks->type == TOK_WORD)
			command_and_suffix(cmd, toks, &j);
		if (toks->type == TOK_LESS || toks->type == TOK_GREAT)
			redirect(cmd, &toks, toks->type, ft_strlen(toks->content));
		toks = toks->next;
	}
	if (toks != NULL && !(toks->type == TOK_PIPE && !toks->next))
		create_next_command(&cmd, &toks);
	else
	{
		cmd->next = NULL;
		free_toks(head);
	}
}
