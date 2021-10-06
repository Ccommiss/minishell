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
	static enum tokens	tok[40][256] = {
		[OP] = {
			['|'] = TOK_PIPE,
			['<'] = TOK_LESS,
			['>'] = TOK_GREAT,
			['='] = TOK_EQUAL
		},
		[SQUOTE] = {
			['\0'...u'ÿ'] = TOK_WORD,
		},
		[DQUOTE] = {
			['\0'...u'ÿ'] = TOK_WORD,
		},
		[WORD] = {
			[' '] = TOK_EAT, // CARACTERE D'ARRET
			['#'...'&'] = TOK_WORD, // 35 a 38
			['('...'/'] = TOK_WORD, //40 a 47
			['0'...'9'] = TOK_WORD, //48 a 57
			[':'...';'] = TOK_WORD,
			['='] = TOK_WORD,
			['?'...'@'] = TOK_WORD, // 58 a 59 et 61, 63, 64
			['A'...'z'] = TOK_WORD, //97 a 122
			['{'] = TOK_WORD,
			['}'] = TOK_WORD, //123,125
			['~'...u'ÿ'] = TOK_WORD, // 126 a la fin
			['|'] = TOK_PIPE,
			['<'] = TOK_LESS,
			['>'] = TOK_GREAT,
			['\''] = TOK_WORD, //39
			['\"'] = TOK_WORD, //34
		}
	};

	return (tok[x][y]);
}

void	handle_quoted_context(int *context, int *i, char *to_tokenize)
{
	if (*context != DQUOTE && *context != SQUOTE && (to_tokenize[*i] == SQUOTE && ft_strchr(to_tokenize + *i +1, SQUOTE)))
	{
		*i += 1;
		*context = SQUOTE;
	}
	else if (*context != SQUOTE && *context != DQUOTE && (to_tokenize[*i] == DQUOTE && ft_strchr(to_tokenize + *i +1, DQUOTE)))
	{
		*i += 1;
		*context = DQUOTE;
	}
	else if ((*context == SQUOTE && to_tokenize[*i] == SQUOTE) || (*context == DQUOTE && to_tokenize[*i] == DQUOTE))
	{
		*i += 1;
		*context = corresp[(int)to_tokenize[*i]];
	}
	if ((int)to_tokenize[*i] == SQUOTE || (int)to_tokenize[*i] == DQUOTE) // test pour gerer si "" collees
		handle_quoted_context(context, i, to_tokenize);
	printf ("i = %d CONTXT = %d\n", *i, *context);
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
	t_token *head;
	ft_bzero(token, 2048);

	printf ("tok 0 = %d // corresp = %d \n", (unsigned char)to_tokenize[0], corresp[(unsigned char)to_tokenize[0]]);
	ref_char = tok(corresp[(unsigned char)to_tokenize[0]], (unsigned char)to_tokenize[0]);
	if (ref_char == 0)
		exit (0);
	context = corresp[(unsigned char)to_tokenize[0]];
	if (context == SQUOTE || context == DQUOTE)
		context = WORD;

	head = toks;
	while ((to_tokenize[i]) && ref_char == (int)tok(context, (unsigned char)to_tokenize[i]))
	{
		handle_quoted_context(&context, &i, to_tokenize);
		if (ref_char != (int)tok(context, (unsigned char)to_tokenize[i]))
				break ;
		if (to_tokenize[i] == '$' && context != SQUOTE)
		{
			int j;
			j = 0;
			printf ("VAR to_tokenize %s \n", to_tokenize);
			while (to_tokenize[i+j] && to_tokenize[i+j+1] != ' ' && to_tokenize[i+j+1] != DQUOTE) //test le +1 pour pas envoyer lespace
				j++;
			if (j > 1) // si on a plus que juste le $
				to_tokenize = ft_str_replace(to_tokenize, i, j, env);
			handle_quoted_context(&context, &i, to_tokenize); // TEST
		}
		token[buf_i++] = to_tokenize[i];
		if (to_tokenize[i])
			i++;
	}
	token[buf_i] = '\0';
	if (ref_char != TOK_EAT)
	{
		toks->content = ft_strdup(token);
		printf ("%s \n", toks->content);
		toks->type = ref_char;
		toks->len = strlen(toks->content);
		toks->next = malloc(sizeof(t_token));
		toks->next->prev = toks;
		toks->next->index = toks->index + 1;
		toks = toks->next;
	}
	to_tokenize = ft_substr(to_tokenize, i, ft_strlen(to_tokenize));
	if (ft_strlen(to_tokenize) != 0)
		tokenize(to_tokenize, toks, env); //recursivite
	else
	{
		toks = toks->prev;
		free(toks->next);
		toks->next = NULL;
	}
}
