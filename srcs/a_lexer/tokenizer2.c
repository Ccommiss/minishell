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
	lex->exp_res = 0;
}

void	lex_error_detector(t_token *toks)
{
	char	tok_op;

	if (toks->type == TOK_GREAT)
		tok_op = '>';
	if (toks->type == TOK_LESS)
		tok_op = '<';
	if (toks->type == TOK_PIPE)
		tok_op = '|';
	if (((toks->type == TOK_GREAT || toks->type == TOK_LESS) && toks->len > 2)
		|| (toks->type == TOK_PIPE && toks->len > 1))
	{
		toks->type = SYNT_ERR;
		if (return_value != 2)
			printf("minishell : syntax error near \"%c\"\n", tok_op);
		return_value = 2;
	}
}

void	create_token(t_token **toks, t_lex *l)
{
	if ((*toks)->content == NULL)
		(*toks)->content = ft_strdup(l->token);
	(*toks)->type = l->ref_char;
	(*toks)->len = strlen((*toks)->content);
	lex_error_detector(*toks);
	(*toks)->next = malloc(sizeof(t_token));
	(*toks)->next->content = NULL;
	(*toks)->next->prev = (*toks);
	(*toks)->next->index = (*toks)->index + 1;
	(*toks) = (*toks)->next;
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

	to_tokenize = ft_strdup(line);
	init_lexer_struct(&l, to_tokenize);
	i = 0;
	while ((to_tokenize[i])
		&& l.ref_char == (int)tok(l.context, (unsigned char)to_tokenize[i]))
	{
		handle_quoted_context(&(l.context), &i, to_tokenize);
		if (l.ref_char != (int)tok(l.context, (unsigned char)to_tokenize[i]))
			break ;
		while (to_tokenize[i] == '$' && l.context != SQUOTE
			&& l.exp_res != 2) //2 voudra dire juste un seul $
		{
			l.exp_res = expand(&to_tokenize, &i, &l.context, env);
			if (l.exp_res == -1) //echec expand
			{
				l.ref_char = TOK_ERR;
				ft_bzero(l.token, 2048);
				while (to_tokenize[i] && to_tokenize[i] != '|')
					i++;
				break ;
			}
		}
		//if (l.ref_char != (int)tok(l.context, (unsigned char)to_tokenize[i]))
		//		break ;
		l.token[l.buf_i++] = to_tokenize[i];
		if (to_tokenize[i])
			i++;
	}
	l.token[l.buf_i] = '\0';
	if (l.ref_char != TOK_EAT && ft_strlen(l.token) != 0)
		create_token(&toks, &l);
	to_tokenize = ft_auto_substr(to_tokenize, i, ft_strlen(to_tokenize));
	if (to_tokenize && ft_strlen(to_tokenize) != 0)
		tokenize(to_tokenize, toks, env); //recursivite
	else if (toks && toks->prev)
	{
		toks = toks->prev;
		free(toks->next);
		toks->next = NULL;
	}
	else
		toks = NULL;
	free(to_tokenize);
	to_tokenize = NULL;
}
