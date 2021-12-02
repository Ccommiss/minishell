/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_error_detector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:59:10 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/02 15:59:11 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum tokens	error_tab(int type)
{
	static enum tokens	op_table[256] = {
	[TOK_GREAT] = OP,
	[TOK_LESS] = OP,
	[TOK_PIPE] = OP
	};

	return (op_table[type]);
}

int	is_op(int type)
{
	static int	op_table[256] = {
	[TOK_GREAT] = TRUE,
	[TOK_LESS] = TRUE,
	[TOK_PIPE] = FALSE
	};

	return (op_table[type]);
}

/*
**	syntax_error_detector handles :
**	- if more than expected operators are found (ex. <<<, ||, etc)
**	- if operators are doubled (ex echo lol > >> file), e.g.
**		not preceded by a TOK_WORD token
** 	- reste a gerer -> si TOK en fin de ligne
**   - NEXT TOK IS ALWAYS NULL as this function is called in each tok
*/
void	syntax_error_detector(t_token *toks, int last_tok_is_op)
{
	char	tok_op;

	if (toks->type == TOK_GREAT)
		tok_op = '>';
	if (toks->type == TOK_LESS)
		tok_op = '<';
	if (toks->type == TOK_PIPE)
		tok_op = '|';
	if (((toks->type == TOK_GREAT || toks->type == TOK_LESS) && toks->len > 2)
		|| (toks->type == TOK_PIPE && toks->len > 1)
		|| ((toks->type == TOK_PIPE && !toks->prev)
			|| (toks->prev && error_tab(toks->type) == OP
				&& toks->prev->type == toks->type))
		|| (toks->type == TOK_PIPE && is_op(toks->prev->type) == TRUE)
		|| last_tok_is_op == TRUE)
	{
		toks->type = SYNT_ERR;
		if (return_value != 2)
			printf("minishell : syntax error near \"%c\"\n", tok_op);
		return_value = 2;
	}
}

/*
**	Prints expand errors for :
**	- Open brace (ex : ${var   )
**	- Bad subsitution (when non alphanum character is found in {} )
*/

int	print_expand_errors(int error_type, char *var_name, char *trimmed_var)
{
	if (error_type == OPEN_BRACE)
	{
		printf("%s : brace error, please close them\n", var_name);
		return_value = 1;
		free(var_name);
		return (ERROR);
	}
	if (error_type == BAD_SUBSTIT)
	{
		printf("%s : bad substitution\n", var_name);
		return_value = 1;
		free(var_name);
		free(trimmed_var);
		return (ERROR);
	}
	return (0);
}

/*
** 	Expand finds the var name to tokenize in the user input and send it
**	to be replaced.
*/

int	expand_substitution_error_detector(char *var_name, int exception)
{
	char	*trimmed_var;

	if (exception == OPEN_BRACE)
		return (print_expand_errors(OPEN_BRACE, var_name, NULL));
	if (exception == CLOSE_BRACE)
		trimmed_var = ft_substr(var_name, 2, ft_strlen(var_name) - 3);
	else
		trimmed_var = ft_substr(var_name, 1, ft_strlen(var_name) - 1);
	if (!trimmed_var)
		return (MALLOC_FAIL);
	if (!ft_isalnum_str(trimmed_var)
		&& ft_strncmp(trimmed_var, "?", 2) != 0
		&& ft_strncmp(trimmed_var, "$", 2) != 0)
		return (print_expand_errors(BAD_SUBSTIT, var_name, trimmed_var));
	free(trimmed_var);
	free(var_name);
	return (0);
}
