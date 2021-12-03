/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:46:53 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/03 18:42:30 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_return_value;

char	*choose_prompt(void)
{
	char	*line;

	if ((!isatty(STDIN_FILENO)))
	{
		rl_outstream = stdin;
		line = readline("");
		return (line);
	}
	if (g_return_value != 0)
		line = readline(BWHT "Minishell " BRED "> " RESET);
	else
		line = readline(BWHT "Minishell " BGRN "> " RESET);
	return (line);
}

void	quit_from_main(t_env *env)
{
	clean_env(env);
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	exit(0);
}

void	shell_loop(char **line, t_env **env)
{
	t_token	toks;
	t_cmd	cmd;

	if (check_quote(*line) != 0 || line_length(*line) != 0)
		return ;
	init_tok_and_cmd(&toks, &cmd);
	tokenize(*line, &toks, *env);
	debug_tokens(&toks);
	token_to_cmds(&cmd, &toks);
	find_path(&cmd, *env);
	debug_cmds(&cmd);
	cmd_to_exec(&cmd, *env, *line);
	cleanup(&cmd, &toks, *line);
}

int	error_management(int ac, char **envp)
{
	if (envp[0] == NULL)
	{
		printf("Need environment.\n");
		return (ERROR);
	}
	if (ac > 2)
	{
		printf("Usage: ./minishell\n");
		return (ERROR);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env;

	env = NULL;
	(void)ac;
	(void)av;
	if (error_management(ac, envp) == ERROR)
		return (1);
	get_the_env(&env, envp);
	while (1)
	{
		handle_signal(MAIN_PROCESS);
		line = choose_prompt();
		add_history(line);
		if (line && ft_strlen(line) > 0)
			shell_loop(&line, &env);
		else if (!line)
			quit_from_main();
	}
	return (0);
}
