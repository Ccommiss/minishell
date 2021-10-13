#include "minishell.h"

/*
**	Memo ASCII
**
**	0 a 32 : non-printable characters
**	33 ... 47 : ponctuation
**		├─> 34 : "
**		├─> 36 : $
**		├─> 39 : '
**	48 a 57 : chiffres
**	58 a 64 : operateurs
**		├─> 60 : <
**		├─> 62 : >
**	65 a 90 : A a Z
**	91 a 96 : ponctuation '[' a '`'
**	97 a 122 : a a z
**	123 a 127 : ponctuation { a ~ puis DEL
**	128 a 254 : Ascii extended
*/

static enum tokens	corresp[256] = {
	['|'] = OP,
	['<'] = OP,
	['>'] = OP,
	['\0'...'!'] = WORD, // 0 a 33
	['#'...'&'] = WORD, // 35 a 38
	['('...'/'] = WORD, //40 a 47
	['0'...'9'] = WORD, //48 a 57
	[':'...';'] = WORD,
	['='] = WORD,
	['?'...'@'] = WORD, // 58 a 59 et 61, 63, 64
	['A'...'Z'] = WORD, //65 a 90
	['['...'`'] = WORD, // 91 a 96
	['a'...'z'] = WORD, //97 a 122
	['{'] = WORD,
	['}'] = WORD,
	['~'...u'ÿ'] = WORD, // 126 a la fin
	['\''] = SQUOTE, //39
	['\"'] = DQUOTE, //34
};

enum tokens	tok(int x, int y)
{
	if (x == OP)
		return (op_toks(y));
	if (x == WORD)
		return (word_toks(y));
	if (x == SQUOTE || x == DQUOTE)
		return (quote_toks(y));

	return (WORD);
}

void	handle_quoted_context(int *context, int *i, char *to_tokenize)
{
	printf ("{handle quote} to_tokenize[%d] = %c \n", *i, to_tokenize[*i]);
	if (*context != DQUOTE && *context != SQUOTE
		&& (to_tokenize[*i] == SQUOTE  && ft_strchr(to_tokenize + *i +1, SQUOTE)))
	{
		printf ("ici 1\n");
		*i += 1;
		*context = SQUOTE;
	}
	else if (*context != SQUOTE && *context != DQUOTE
		&& (to_tokenize[*i] == DQUOTE && ft_strchr(to_tokenize + *i +1, DQUOTE)))
	{
		printf ("ici 2\n");

		*i += 1;
		*context = DQUOTE;
	}
	else if ((*context == SQUOTE && to_tokenize[*i] == SQUOTE)
		|| (*context == DQUOTE && to_tokenize[*i] == DQUOTE))
	{
		*i += 1;
		*context = WORD;
	}
	printf ("context after handle = %c \n", *context);
//	sleep (2);
	if (((int)to_tokenize[*i] == SQUOTE && *context != DQUOTE)
		|| ((int)to_tokenize[*i] == DQUOTE && *context != SQUOTE)) // test pour gerer si "" collees
		handle_quoted_context(context, i, to_tokenize);
}


/*
**	@param to_tokenize : chaine de commande
**	@t_token
*/
void tokenize(char *to_tokenize, t_token *toks, t_env *env) // fonction recursive
{
	int i = 0;
	int ref_char = -100;
	int buf_i = 0;
	char token[2048];
	int context;

	ft_bzero(token, 2048);

//	printf ("tok 0 = %d // corresp = %d \n", (unsigned char)to_tokenize[0], corresp[(unsigned char)to_tokenize[0]]);
	ref_char = tok(corresp[(unsigned char)to_tokenize[0]], (unsigned char)to_tokenize[0]);
	context = corresp[(unsigned char)to_tokenize[0]];
	if (context == SQUOTE || context == DQUOTE)
		context = WORD;

	while ((to_tokenize[i]) && ref_char == (int)tok(context, (unsigned char)to_tokenize[i]))
	{
		handle_quoted_context(&context, &i, to_tokenize);
		if (ref_char != (int)tok(context, (unsigned char)to_tokenize[i]))
				break ;
		if (to_tokenize[i] == '$' && context != SQUOTE)
		{
			if (expand(&to_tokenize, &i, &context, env) == -1) //echec expand
			{
				ref_char = TOK_ERR; //trouver la variable fautive 
				toks->content = ft_strdup("nom var : bad substitution a gerer\n");
				while (to_tokenize[i] && to_tokenize[i] != '|')
					i++;
				break ;
			}
		}	
		if (ref_char != (int)tok(context, (unsigned char)to_tokenize[i]))
				break ;
		token[buf_i++] = to_tokenize[i];
		if (to_tokenize[i])
			i++;
	}
	token[buf_i] = '\0';
	if (ref_char != TOK_EAT)
	{
		if(toks->content == NULL)
			toks->content = ft_strdup(token);
		//printf ("content = %s")
		toks->type = ref_char;
		toks->len = strlen(toks->content);
		toks->next = malloc(sizeof(t_token));
		toks->next->content = NULL; //faire fonction init 
		toks->next->prev = toks;
		toks->next->index = toks->index + 1;
		toks = toks->next;
	}
	to_tokenize = ft_substr(to_tokenize, i, ft_strlen(to_tokenize));
	if (ft_strlen(to_tokenize) != 0)
		tokenize(to_tokenize, toks, env); //recursivite
	else if (toks && toks->prev)
	{
		toks = toks->prev;
		free(toks->next);
		toks->next = NULL;
	}
	else 
	{
		printf ("rien du tout %p \n", toks);
		toks = NULL;
		printf ("rien du tout %p \n", toks);
	}
}
