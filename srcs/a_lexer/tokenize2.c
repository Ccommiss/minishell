





#include "../../include/minishell.h"

static int alnum[255] = {
	['A' ... 'Z'] = 1,
	['a' ... 'z'] = 1,
	['$'] = 1,
	['\''] = 1,
	['\"'] = 1,
	[0 ... 9] = 1

};

static int corresp[255] = {
	['|'] = OP,
	['<'] = OP,
	['>'] = OP,
	['A' ... 'Z'] = WORD,
	['a' ... 'z'] = WORD,
	['$'] = WORD,
	[0 ... 9] = WORD,
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
	[QUOTE] = {['|'] = TOK_WORD, ['<'] = TOK_WORD, ['>'] = TOK_WORD, ['\''] = TOK_WORD, ['\"'] = TOK_WORD, ['A' ... 'Z'] = TOK_WORD, ['a' ... 'z'] = TOK_WORD, ['$'] = TOK_WORD, [' '] = TOK_WORD, [0 ... 9] = TOK_WORD

	},
	[WORD] = {
		[' '] = TOK_EAT, // CARACTERE D'ARRET, alors que non si on est dans des quotes
		['A' ... 'Z'] = TOK_WORD,
		['a' ... 'z'] = TOK_WORD,
		['$'] = TOK_WORD,
		['\''] = TOK_WORD,
		['\"'] = TOK_WORD,
		[0 ... 9] = TOK_WORD,
		['|'] = TOK_PIPE,
		['<'] = TOK_LESS,
		['>'] = TOK_GREAT,
	},
	[VAR] = {
		[' '] = TOK_EAT, // CARACTERE D'ARRET, alors que non si on est dans des quotes
		['A' ... 'Z'] = TOK_WORD,
		['a' ... 'z'] = TOK_WORD,
		['$'] = TOK_WORD,
		['\''] = TOK_WORD,
		['\"'] = TOK_WORD,
		[0 ... 9] = TOK_WORD,
		['|'] = TOK_WORD,
		['<'] = TOK_WORD,
		['>'] = TOK_WORD
	}

};



char *ft_str_replace(char *str, int start, int len)
{
	int i;
	i = 0;
//	printf ("len = %d \n", len);
	while (i < start)
		i++;
	//str[i] = ' '; // test pour espaces
	//i++;
	while (i < start + len)
	{
		str[i++] = '|';
	}
//	printf ("replaced %s \n", str);
	return (str);
}
/*
**	@param to_tokenize : chaine de commande
**	@t_token
*/
void tokenize(char *to_tokenize, t_token *toks) // fonction recursive
{
	int i = 0;
	int ref_char = -100;
	static int ind = 0;

	ref_char = tok[corresp[to_tokenize[0]]] [to_tokenize[0]] ; //le type de reference sera le typ[e du premier char
										//ex Tok_Word
										// But = tous les autres = des toks words aussi

	int context;
	context = corresp[to_tokenize[0]];
	//printf ("context = %d \n", context);
	if (context == QUOTE)
		context = WORD;
	while (to_tokenize[i] && ref_char == tok[context][to_tokenize[i]])
	{

		//printf ("%c -- %d \n", to_tokenize[i], tok[context][to_tokenize[i]]);
		//i++;
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
			while (to_tokenize[i+j] && to_tokenize[i+j] != ' ')
				j++;
			to_tokenize = ft_str_replace(to_tokenize, i, j);
			//i += j - 1;
			i -= 1; //pour reanalyser le $ avec comment il a ete replaced
		}
		i++;
	}
	if (ref_char != TOK_EAT)
	{
		toks->content = ft_substr(to_tokenize, 0, i);
		toks->index = ind;
		ind++;
		toks->type = ref_char;
		toks->len = strlen(toks->content);
		toks->next = malloc(sizeof(t_token));
		toks->next->prev = toks;
		printf("[%d] => len = %3d tok type = %d content = |%s|\n", toks->index, toks->len, toks->type, toks->content);
		toks = toks->next;
	}
	to_tokenize = ft_substr(to_tokenize, i, ft_strlen(to_tokenize));
	//printf("new tokenize = |%s| \n", to_tokenize);
	if (ft_strlen(to_tokenize) != 0)
		tokenize(to_tokenize, toks); //recursivite
	//else

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

int main(int argc, char **argv)
{

	t_token toks;
	int i = 0;
	i = -1;

	if (argc > 2)
	{
		printf("Only one str pls \n");
		exit(0);
	}
	tokenize(argv[1], &toks);
	//remove_toks_quotes(&toks);
}
