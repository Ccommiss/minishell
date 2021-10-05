





#include "minishell.h"

static enum tokens corresp[255] = {
	['|'] = OP,
	['<'] = OP,
	['>'] = OP,
	['A' ... 'Z'] = WORD,
	['a' ... 'z'] = WORD,
	['$'] = WORD,
	['-'] = WORD,
	['='] = WORD,
	['0' ... '9'] = WORD,
	[' '] = WORD,
	['\''] = SQUOTE,
	['\"'] = DQUOTE,
};

static enum tokens tok[40][255] = {
	[OP] = {
		['|'] = TOK_PIPE,
		['<'] = TOK_LESS,
		['>'] = TOK_GREAT,
		['='] = TOK_EQUAL
	},
	[DQUOTE] = {
		[0 ... 254] = TOK_WORD,
	},
	[SQUOTE] = {
		[0 ... 254] = TOK_WORD,
	},
	[WORD] = {
		[' '] = TOK_EAT, // CARACTERE D'ARRET, alors que non si on est dans des quotes
		['A' ... 'Z'] = TOK_WORD,
		['a' ... 'z'] = TOK_WORD,
		['0' ... '9'] = TOK_WORD,
		[33 ... 47] = TOK_WORD, // caracteres de ponctuations surtout
		['='] = TOK_WORD,
		[':'] = TOK_WORD,
		[';'] = TOK_WORD,
		['|'] = TOK_PIPE,
		['<'] = TOK_LESS,
		['>'] = TOK_GREAT,
	}
};



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
	ref_char = tok[corresp[(int)to_tokenize[0]]] [(int)to_tokenize[0]] ; //le type de reference sera le typ[e du premier char
										//ex Tok_Word
										// But = tous les autres = des toks words aussi

	context = corresp[(int)to_tokenize[0]];
	//printf ("context = %d \n", context);
	if (context == SQUOTE || context == DQUOTE)
		context = WORD;

	head = toks;
	while ((to_tokenize[i]) && ref_char == (int)tok[context][(int)to_tokenize[i]])
	{
		//printf ("%c \n ", to_tokenize[i]);
		handle_quoted_context(&context, &i, to_tokenize);
			if (ref_char != (int)tok[context][(int)to_tokenize[i]])
				break ;

		if (to_tokenize[i] == '$' && context != SQUOTE)
		{
			int j;
			j = 0;
			while (to_tokenize[i+j] && to_tokenize[i+j+1] != ' ' && to_tokenize[i+j+1] != DQUOTE) //test le +1 pour pas envoyer lespace
				j++;
			if (j > 1) // si on a plus que juste le $
				to_tokenize = ft_str_replace(to_tokenize, i, j, env);
		}
		token[buf_i++] = to_tokenize[i];
		i++;
	}
	token[buf_i] = '\0';
	if (ref_char != TOK_EAT)
	{
		toks->content = ft_strdup(token);
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
