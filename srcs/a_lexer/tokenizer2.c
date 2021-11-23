#include "minishell.h"

void	init_lexer_struct(t_lex *lex, char *to_tokenize)
{
	ft_bzero(lex->token, 2048);
	lex->buf_i = 0;
	lex->ref_char = tok(corresp((unsigned char)to_tokenize[0]),
			(unsigned char)to_tokenize[0]);
	lex->context = corresp((unsigned char)to_tokenize[0]);
	if (lex->context == SQUOTE || lex->context == DQUOTE)
		lex->context = WORD;
<<<<<<< HEAD
	lex->exp_res = -1;
=======
	lex->exp_res = -2;
>>>>>>> main
}

void	create_token(t_token **toks, t_lex *l)
{
	if ((*toks)->content == NULL && l->ref_char != TOK_NO_VAR) //test
		(*toks)->content = ft_strdup(l->token);
	else
		(*toks)->content = NULL;
	(*toks)->type = l->ref_char;
	if ((*toks)->content)
		(*toks)->len = strlen((*toks)->content);
	else 
		(*toks)->len =-1;
	syntax_error_detector(*toks, FALSE);
	(*toks)->next = malloc(sizeof(t_token));
	(*toks)->next->content = NULL;
	(*toks)->next->prev = (*toks);
	(*toks)->next->index = (*toks)->index + 1;
	(*toks) = (*toks)->next;
}

int	handle_expand(char **to_tokenize, int *i, t_lex *l, t_env *env)
{
	int old_context;
	int old_exp;
	int old_i;

	old_context = l->context;
	old_exp = l->exp_res;
	old_i = *i;
	
	while (to_tokenize[0][*i] == '$' && l->context != SQUOTE && l->exp_res != 2)
	{
		l->exp_res = expand(to_tokenize, i, &l->context, env);
		if (l->exp_res == ERROR)
		{
			l->ref_char = TOK_ERR;
			ft_bzero(l->token, 2048);
			while (to_tokenize[0][*i] && to_tokenize[0][*i] != '|')
				*i += 1;
			return (ERROR);
		}
		if (old_context == WORD && (int)tok(l->context, (unsigned char)to_tokenize[0][*i]) == TOK_EAT 
		&& old_exp != 0 && old_i == 0) // je crois que du coup pas besoin du old_expcar old_i prime ? pas sur 
		{
			l->exp_res = 404;
			l->ref_char = TOK_NO_VAR;
		}
	}
	if (l->ref_char != (int)tok(l->context, (unsigned char)to_tokenize[0][*i]))
		return (BREAK);
	return (0);
}

void	fill_token_buff(t_lex *l, char **to_tokenize, int *i, t_env *env)
{
	while (to_tokenize[0][*i]
		&& l->ref_char == (int)tok(l->context,
			(unsigned char)to_tokenize[0][*i]))
	{
		handle_quoted_context(&(l->context), i, *to_tokenize);
		if (handle_expand(to_tokenize, i, l, env) == -1)
			break ;
		l->token[l->buf_i++] = to_tokenize[0][*i];
		if (to_tokenize[0][*i])
			*i += 1;
	}
	l->token[l->buf_i] = '\0';
}

/*
**	tokenize : recursive function that builds a chained list of tokens
**
**	It compares the interpretation of the first char (l.ref_char)
**	with interpretation of next char (to_tokenize[i])
**	@param to_tokenize : chaine de commande
**	@t_token
*/
void	tokenize(char *line, t_token *toks, t_env *env)
{
	t_lex	l;
	int		i;
	char	*to_tokenize;

	i = 0;
	to_tokenize = ft_strdup(line);
	init_lexer_struct(&l, to_tokenize);
	fill_token_buff(&l, &to_tokenize, &i, env);
	if (l.ref_char != TOK_EAT)// && l.exp_res != 404)// && ft_strlen(l.token) != 0)
		create_token(&toks, &l);
	l.exp_res = -2;
	to_tokenize = ft_auto_substr(to_tokenize, i, ft_strlen(to_tokenize));
	if (to_tokenize && ft_strlen(to_tokenize) != 0)
		tokenize(to_tokenize, toks, env);
	else if (toks && toks->prev)
	{
		toks = toks->prev;
		free(toks->next);
		toks->next = NULL;
		if (error_tab(toks->type) == OP)
			syntax_error_detector(toks, TRUE);
	}
	free(to_tokenize);
	to_tokenize = NULL;
}
