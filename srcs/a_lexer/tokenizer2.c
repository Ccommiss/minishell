





#include "minishell.h"

static int corresp[255] = {
	['|'] = OP,
	['<'] = OP,
	['>'] = OP,
	['A' ... 'Z'] = WORD,
	['a' ... 'z'] = WORD,
	['$'] = WORD,
	['-'] = WORD,
	['0' ... '9'] = WORD,
	[' '] = WORD,
	['\''] = QUOTE,
	['\"'] = QUOTE,
};

static enum tokens tok[4][255] = {
	[OP] = {
		['|'] = TOK_PIPE,
		['<'] = TOK_LESS,
		['>'] = TOK_GREAT,
	},
	[QUOTE] = {
		[0 ... 254] = TOK_WORD,
	},
	[WORD] = {
		[' '] = TOK_EAT, // CARACTERE D'ARRET, alors que non si on est dans des quotes
		['A' ... 'Z'] = TOK_WORD,
		['a' ... 'z'] = TOK_WORD,
		['0' ... '9'] = TOK_WORD,
		[33 ... 47] = TOK_WORD, // caracteres de ponctuations surtout
		[':'] = TOK_WORD,
		[';'] = TOK_WORD,
		['|'] = TOK_PIPE,
		['<'] = TOK_LESS,
		['>'] = TOK_GREAT,
	},
	[VAR] = {
		[' '] = TOK_EAT, // CARACTERE D'ARRET, alors que non si on est dans des quotes, ajouter tous les espaces
		['A' ... 'Z'] = TOK_WORD,
		['a' ... 'z'] = TOK_WORD,
		[':'] = TOK_WORD,
		[';'] = TOK_WORD,
		['0' ... '9'] = TOK_WORD,
		[33 ... 47] = TOK_WORD, // caracteres de ponctuations surtout
		['|'] = TOK_WORD,
		['<'] = TOK_WORD,
		['>'] = TOK_WORD,
	//	['-'] = TOK_WORD
	}

};


//reste a gerer si var existe aps

/*
**	@param to_tokenize : chaine de commande
**	@t_token
*/
void tokenize(char *to_tokenize, t_token *toks, t_env *env) // fonction recursive
{
	int i = 0;
	int ref_char = -100;
	//static int ind = 0;

	ref_char = tok[corresp[(int)to_tokenize[0]]] [(int)to_tokenize[0]] ; //le type de reference sera le typ[e du premier char
										//ex Tok_Word
										// But = tous les autres = des toks words aussi

	int context;
	context = corresp[(int)to_tokenize[0]];
	//printf ("context = %d \n", context);
	if (context == QUOTE)
		context = WORD;




	while (to_tokenize[i] && ref_char == (int)tok[context][(int)to_tokenize[i]])
	{
		//printf ("%c -- %d \n", to_tokenize[i], tok[context][(int)to_tokenize[i]]);
		if ( context != QUOTE &&
			( (to_tokenize[i] == SQUOTE && ft_strchr(to_tokenize + i +1, SQUOTE))
			|| (to_tokenize[i] == DQUOTE && ft_strchr(to_tokenize + i + 1, DQUOTE))
			)
		)
		{
			context = QUOTE;
		}
		else if (context == QUOTE && (to_tokenize[i] == SQUOTE || to_tokenize[i] == DQUOTE))
			context = WORD;

		else if (to_tokenize[i] == '$' && context != QUOTE)
		{
			int j;
			j = 0;
			context = VAR;
			while (to_tokenize[i+j] && to_tokenize[i+j+1] != ' ') //test le +1 pour pas envoyer lespace
				j++;
			to_tokenize = ft_str_replace(to_tokenize, i, j, env);
			i -= 1; //pour reanalyser le $ avec comment il a ete replaced
		}
		i++;
	}
	if (ref_char != TOK_EAT)
	{
		toks->content = ft_substr(to_tokenize, 0, i);
		toks->type = ref_char;
		toks->len = strlen(toks->content);
		toks->next = malloc(sizeof(t_token));
		toks->next->prev = toks;
		toks->next->index = toks->index + 1;
		toks = toks->next;
	}
	to_tokenize = ft_substr(to_tokenize, i, ft_strlen(to_tokenize));
	//printf("new tokenize = |%s| \n", to_tokenize);
	if (ft_strlen(to_tokenize) != 0)
		tokenize(to_tokenize, toks, env); //recursivite
	else
	{
		toks->next = NULL;
		while(toks->index != 0)
			toks = toks->prev;
	}

}


void remove_toks_quotes(t_token *toks)
{
	while (toks)
	{
		printf("%d \n", toks->index);
		if (toks->content[0] == SQUOTE)
			toks->content = ft_strtrim(toks->content, "'");
		else if (toks->content[0] == DQUOTE)
			toks->content = ft_strtrim(toks->content, "\"");
		printf("trimmed :%s \n", toks->content);
		toks = toks->next;
	}
}

// int main(int argc, char **argv)
// {

// 	t_token toks;
// 	int i = 0;
// 	i = -1;

// 	if (argc > 2)
// 	{
// 		printf("Only one str pls \n");
// 		exit(0);
// 	}
// }
