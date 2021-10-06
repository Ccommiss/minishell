


#include "minishell.h"

void init_cmd(t_cmd *cmd)
{
	cmd->cmd_args = malloc(sizeof(char **) * 1);
	cmd->index = 0;
	if (cmd->prev != NULL)
		cmd->index = cmd->prev->index + 1;

	cmd->io_in = NOT_SPECIFIED;
	cmd->io_out = NOT_SPECIFIED;
	cmd->dgreat = FALSE;
	cmd->dless = FALSE;
}

t_cmd *token_to_cmds(t_cmd *cmd, t_token *toks)
{
	int j = 0;
	init_cmd(cmd);

	if (toks->type == TOK_PIPE)
		toks = toks->next;
	while (toks && toks->type != TOK_PIPE)
	{
		if (toks->type == TOK_WORD)
		{
			cmd->cmd_args = realloc(cmd->cmd_args, (sizeof(char **) * (j + 2)));
			cmd->cmd_args[j] = ft_strdup(toks->content);
			j++;
			cmd->cmd_args[j] = NULL;
		}
		if (toks->type == TOK_LESS)
		{
			if (!toks->next)
				return (NULL); //reetourner une erreur
			if (ft_strlen(toks->content) == 1)
			{
				toks = toks->next;
				cmd->io_in = open(toks->content, O_RDWR | O_TRUNC | O_CREAT);
			}
			else if (ft_strlen(toks->content) == 2)
			{
				toks = toks->next;
				cmd->io_in = open(toks->content, O_RDWR | O_APPEND | O_CREAT);
				cmd->dless = TRUE;
			}
		}
		else if (toks->type == TOK_GREAT)
		{
			if (!toks->next)
				return (NULL); //reetourner une erreur
			if (ft_strlen(toks->content) == 1)
			{
				toks = toks->next;
				cmd->io_out = open(toks->content, O_RDWR | O_TRUNC | O_CREAT);
			}
			else if (ft_strlen(toks->content) == 2)
			{
				printf( "ICI >> \n");
				toks = toks->next;
				cmd->io_out = open(toks->content, O_RDWR | O_APPEND | O_CREAT);
				cmd->dgreat = TRUE;
			}
		}
		toks = toks->next;
	}

	if (toks != NULL)
	{
		cmd->next = malloc(sizeof(t_cmd));
		cmd->next->prev = cmd;
		token_to_cmds(cmd->next, toks);
	}
	else
		cmd->next = NULL;


	return cmd;
}
