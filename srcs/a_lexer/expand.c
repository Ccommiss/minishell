/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:57:28 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/03 19:32:30 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	extract_pure_var_name : "purifies" var_name so it removes
**		- case 1 : $ symbole and {} both braces (eg: ${PATH} becomes PATH)
**		- case 2 : only $ symbol
*/
void	extract_pure_var_name(char **var_name, int len, int start, char *str)
{
	if (str[start + 1] == '{')
		*var_name = ft_substr(str, start + 2, len - 2);
	else
		*var_name = ft_substr(str, start + 1, len);
}

/*
**	assign_value : return "values" as the expanded var
**		- 1) handles 2 special cases : $$ and $?
**		- 2) iterates through the env to see if one
**			value match the provided key (var_name)
*/
char	*assign_value(t_env *env, char *var_name)
{
	if (ft_strncmp(var_name, "?", 1) == 0)
		return (ft_itoa(g_return_value));
	else if (ft_strncmp(var_name, "$", 1) == 0)
		return (ft_itoa(getpid()));
	while (env && ft_strncmp(var_name, env->key, ft_strlen(env->key) + 1) != 0)
		env = env->next;
	if (env == NULL)
		return (ft_strdup(""));
	else
		return (ft_strdup(env->value));
}

/*
**	ft_str_replace finds the value associated to the provided variable
**	key iterating through the env variable.
**
**	- var_name : var without $ and eventually braces {}
**	- value : value associated to $key in env
**	- tmp : if start != 0, what was before the $ in the same token eg. hello$var
**		tmp would return hello
**	- new_str = concat of what was before + value eg. hello$var
**		become helloworld (if $var = world)
**	- second new_str = concat new_str with remaining of str
**		eg what was after.
**		"hello$var that was what was after $lol" becomes
**		"helloworld that was what was after $lol"
*/
char	*ft_str_replace(char *str, int start, int len, t_lex **l)
{
	char	*var_name;
	char	*new_str;
	char	*value;
	char	*tmp;

	extract_pure_var_name(&var_name, len, start, str);
	value = assign_value(*((**l).env), var_name);
	(*l)->exp_len = ft_strlen(value);
	free(var_name);
	tmp = ft_substr(str, 0, start);
	new_str = ft_strconcat(tmp, value, start + ft_strlen(value));
	free(tmp);
	tmp = ft_strdup(new_str);
	free(new_str);
	new_str = ft_strconcat(tmp, str + start + len + 1,
			ft_strlen(tmp) + ft_strlen(str + start + len));
	free(tmp);
	free(value);
	free(str);
	return (new_str);
}

/*
** expand : extract the expand var and replace the remaining of
** 	the to_tokenize string
*/

int	expand(char **to_tokenize, int *i, t_lex **l, t_env *env)
{
	int		j;
	int		exception;
	char	*var_name;

	if ((*l)->exp_len != 0)
		return (0);
	j = 1;
	exception = 0;
	while (to_tokenize[0][*i + j]
		&& is_valid_expand_char(&exception, to_tokenize[0][*i + j], j))
		j++;
	var_name = ft_substr(*to_tokenize, *(i), j);
	if (!var_name)
		return (MALLOC_FAIL);
	(**l).env = &env;
	if (j == 1)
		return (free_and_return(var_name, 2));
	if (j > 1)
		*to_tokenize = ft_str_replace(*to_tokenize, *i, j - 1, l);
	if ((*l)->exp_len == 0)
		handle_quoted_context(&((*l)->context), i, *to_tokenize);
	return (expand_substitution_error_detector(var_name, exception));
}

int	handle_expand(char **to_tokenize, int *i, t_lex *l, t_env *env)
{
	int	old_context;
	int	old_i;

	old_context = l->context;
	old_i = *i;
	if (l->exp_len > 0 || l->context == SQUOTE)
		return (0);
	while (to_tokenize[0][*i] == '$' && l->context != SQUOTE
		&& l->exp_res != 2 && l->exp_len == 0)
	{
		l->exp_res = expand(to_tokenize, i, &l, env);
		l->context = VAR;
		if (l->exp_res == MALLOC_FAIL)
			return (MALLOC_FAIL);
		if (l->exp_res == ERROR)
			return (create_exp_err_token(to_tokenize, i, l));
		if (old_context == WORD && old_i == 0
			&& tok(l->context, (unsigned char)to_tokenize[0][*i]) == TOK_EAT)
			l->ref_char = TOK_NO_VAR;
	}
	if (l->ref_char != (int)tok(l->context, (unsigned char)to_tokenize[0][*i]))
		return (BREAK);
	return (0);
}
