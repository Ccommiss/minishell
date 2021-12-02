#include "minishell.h"

void free_toks(t_token *toks)
{
	t_token *tmp;
	if (toks->index == -1)
		return ;
	while (toks && toks->index > 0 && toks->index != 0)
		toks = toks->prev;
	while (toks)
	{
		tmp = toks;
		toks = toks->next;
		if (tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		if (tmp->index != 0)
		{
			tmp->index = -1;
			free(tmp);
			tmp = NULL;
		}
	}
}

void free_cmds(t_cmd *cmd)
{
	t_cmd *tmp;

	while (cmd && cmd->index >= 0)
	{
		if (cmd->cmd_args)
			ft_free_double_tab(cmd->cmd_args);
		if (cmd->cmdp)
			free(cmd->cmdp);
		if (cmd->io_here)
			ft_free_double_tab(cmd->io_here);
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->index > 0)
			free((void*)tmp);
	}
}


void	ft_print_error(char *arg)
{
	if (arg != NULL)
		printf("minishell: %s: %s\n", arg, strerror(errno));
	else
		printf("minishell: %s\n", strerror(errno));

}

void cleanup(t_cmd *cmd, t_token *toks, char *line)
{
	free_cmds(cmd);
	// if (toks && toks->next)
	// 	free_toks(toks);
	(void)toks;
	free(line);
}

void	ft_exit_program(t_cmd *cmd, t_token *toks, char *str, void *stuff)
{
	(void)stuff;
	cleanup(cmd, toks, str);
	if (stuff)
		free(stuff);
	exit(1);
}
