#include "minishell.h"



void	handle_quoted_context(int *context, int *i, char *to_tokenize)
{
	if (!to_tokenize[*i]) // test
		return ;
	//printf ("{handle quote} to_tokenize[%d] = %c \n", *i, to_tokenize[*i]);
	if (*context != DQUOTE && *context != SQUOTE
		&& (to_tokenize[*i] == SQUOTE  && ft_strchr(to_tokenize + *i +1, SQUOTE)))
	{
		//printf ("ici 1\n");
		*i += 1;
		*context = SQUOTE;
	}
	else if (*context != SQUOTE && *context != DQUOTE
		&& (to_tokenize[*i] == DQUOTE && ft_strchr(to_tokenize + *i +1, DQUOTE)))
	{
		//printf ("ici 2\n");

		*i += 1;
		*context = DQUOTE;
	}
	else if ((*context == SQUOTE && to_tokenize[*i] == SQUOTE)
		|| (*context == DQUOTE && to_tokenize[*i] == DQUOTE))
	{
		*i += 1;
		*context = WORD;
	}
	if (((int)to_tokenize[*i] == SQUOTE && *context != DQUOTE)
		|| ((int)to_tokenize[*i] == DQUOTE && *context != SQUOTE)) // test pour gerer si "" collees
		handle_quoted_context(context, i, to_tokenize);
}


void	init_lexer_struct(t_lex *lex, char *to_tokenize)
{
	ft_bzero(lex->token, 2048);
	lex->buf_i = 0;
	lex->ref_char = tok(corresp((unsigned char)to_tokenize[0]), (unsigned char)to_tokenize[0]);
	lex->context = corresp((unsigned char)to_tokenize[0]);
	if (lex->context == SQUOTE || lex->context == DQUOTE)
		lex->context = WORD;
}

void	lex_error_detector(t_token *toks)
{
	char tok_op;

	if (toks->type == TOK_GREAT)
			tok_op = '>';
	if (toks->type == TOK_LESS)
		tok_op = '<';
	if (toks->type == TOK_PIPE)
		tok_op = '|';

	if (((toks->type == TOK_GREAT || toks->type == TOK_LESS) && toks->len > 2)
	|| (toks->type == TOK_PIPE &&  toks->len > 1))
	{
		toks->type = SYNT_ERR;
		if (return_value != 2)
		printf("minishell : syntax error near \"%c\"\n", tok_op);
		return_value = 2;
	}
	// if (toks->type == TOK_PIPE &&  toks->len > 1)
	// {
	// 	toks->type = SYNT_ERR;
	// 	printf("minishell : syntax error near \"%c\"\n", toks->type);
	// 	return_value = 2;
	// }
}

void	create_token(t_token **toks, t_lex *l)
{
	if ((*toks)->content == NULL)
		(*toks)->content = ft_strdup(l->token);
		//printf ("content = %s")
	(*toks)->type = l->ref_char;
	(*toks)->len = strlen((*toks)->content);
	lex_error_detector(*toks);
	(*toks)->next = malloc(sizeof(t_token));
	(*toks)->next->content = NULL; //faire fonction init
	(*toks)->next->prev = (*toks);
	(*toks)->next->index = (*toks)->index + 1;
	(*toks) = (*toks)->next;
}
/*
**	@param to_tokenize : chaine de commande
**	@t_token
*/
void tokenize(char *line, t_token *toks, t_env *env) // fonction recursive
{
	t_lex	l;
	int		i;
	char	*to_tokenize;

	to_tokenize = ft_strdup(line);
	init_lexer_struct(&l, to_tokenize);
	i = 0;

	while ((to_tokenize[i]) && l.ref_char == (int)tok(l.context, (unsigned char)to_tokenize[i]))
	{
		handle_quoted_context(&(l.context), &i, to_tokenize);
		if (l.ref_char != (int)tok(l.context, (unsigned char)to_tokenize[i]))
				break ;
		while (to_tokenize[i] == '$' && l.context != SQUOTE && l.exp_res != 2) //2 voudra dire juste un seul $
		{
			l.exp_res = expand(&to_tokenize, &i, &l.context, env);
			if (l.exp_res == -1) //echec expand
			{
				l.ref_char = TOK_ERR; //trouver la variable fautive
				ft_bzero(l.token, 2048);
				printf ("\n");
				while (to_tokenize[i] && to_tokenize[i] != '|')
					i++;
				break ;
			}
		}
		if (l.ref_char != (int)tok(l.context, (unsigned char)to_tokenize[i]))
				break ;
		l.token[l.buf_i++] = to_tokenize[i];
		if (to_tokenize[i])
			i++;
	}
	l.token[l.buf_i] = '\0';
	if (l.ref_char != TOK_EAT)
		create_token(&toks, &l);
	to_tokenize = ft_auto_substr(to_tokenize, i, ft_strlen(to_tokenize));
	if (to_tokenize && ft_strlen(to_tokenize) != 0)
		tokenize(to_tokenize, toks, env); //recursivite
	else if (toks && toks->prev)
	{
		toks = toks->prev;
		free(toks->next);
		toks->next = NULL;
		free(to_tokenize);
		to_tokenize = NULL;
	}
	else
	{
		printf ("rien du tout %p \n", toks);
		toks = NULL;
		printf ("rien du tout %p \n", toks);
	}
	free(to_tokenize);
}
