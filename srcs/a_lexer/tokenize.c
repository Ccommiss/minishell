/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:50:39 by ccommiss          #+#    #+#             */
/*   Updated: 2021/09/24 14:31:43 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static enum tokens tok[3][255] = {
	[OP] = {
		['|'] = TOK_PIPE,
		['<'] = TOK_LESS,
		['>'] = TOK_GREAT,
		//['\''] = SQUOTE,
		//['\"'] = DQUOTE,
	},
	[QUOTE] = {['|'] = TOK_WORD, ['<'] = TOK_WORD, ['>'] = TOK_WORD, ['\''] = TOK_WORD, ['\"'] = TOK_WORD, ['A' ... 'Z'] = TOK_WORD, ['a' ... 'z'] = TOK_WORD, ['$'] = TOK_WORD, [' '] = TOK_WORD, [0 ... 9] = TOK_WORD

	},
	[WORD] = {
		[' '] = TOK_WORD,
		['A' ... 'Z'] = TOK_WORD,
		['a' ... 'z'] = TOK_WORD,
		['$'] = TOK_WORD,
		['\''] = TOK_WORD,
		['\"'] = TOK_WORD,
		[0 ... 9] = TOK_WORD,
		['|'] = TOK_PIPE,
		['<'] = TOK_LESS,
		['>'] = TOK_GREAT,
	}

};

void tokenize(char *to_tokenize, t_token *toks)
{
	int i;
	int j = 0;

	i = 0;
	j = 1;

	printf("\nDEBUG TOKENIZATION\n");
	// Deux cas possibles
	// 1 - Token a 100% meme type
	// 			subtilite : si lol'>'file
	// 2 - Token a rediviser exemple lol>file

	int curr_corres;
	int ind = 0;
	curr_corres = -100;
	while (to_tokenize[i])
	{
		if (curr_corres == -100)
		{
			curr_corres = corresp[to_tokenize[0]]; // exemple : char word
			toks->type = tok[curr_corres][to_tokenize[0]];
		}
		printf("CURR CORRES = %d TOKEN = %c TOKSTYPE = %d\n", curr_corres, to_tokenize[i][j], toks->type);
		if (corresp[to_tokenize[i][ == QUOTE && curr_corres != QUOTE) //premiere quote
		{
			curr_corres = QUOTE;
			//printf ("changement de corresp \n");
			//printf (" toktype %d \n", tok[curr_corres][to_tokenize[i][j]]);
		}
		else if (corresp[to_tokenize[i]] == QUOTE && curr_corres == QUOTE) // quote ferme
			curr_corres = WORD;
		if (tok[curr_corres][to_tokenize[i]] != toks->type)
		{
			printf("char tok actuel %d VS tok de ref %d \n ", tok[curr_corres][to_tokenize[i]], toks->type);
			toks->content = ft_substr(to_tokenize[i], 0, j);
			to_tokenize[i] = ft_substr(to_tokenize[i], j, ft_strlen(to_tokenize[i]));
			printf("new tokenize= %s \n", to_tokenize[i]);
			toks->len = ft_strlen(toks->content);
			toks->index = ind;
			toks->next = malloc(sizeof(t_token));
			toks->next->prev = toks;
			printf("[%d] => len = %3d tok type = %d content = |%s| to exp = %d \n", toks->index, toks->len, toks->type, toks->content, toks->to_expand);
			toks = toks->next;
			ind++;
			j = 0;
			curr_corres = corresp[to_tokenize[i][j]]; // exemple : char word
			toks->type = tok[curr_corres][to_tokenize[i][j]];
			printf("ICI %c %d \n", to_tokenize[i][j], curr_corres);
			//exit (0);
		}
		else
			j++;
	}
	if (to_tokenize[i][j] == 0 && to_tokenize != NULL)
	{
		toks->content = to_tokenize[i];
		printf("NORMAL = %s \n", toks->content);
		toks->len = ft_strlen(toks->content);
		toks->index = ind;
		toks->next = malloc(sizeof(t_token));
		toks->next->prev = toks;
		printf("[%d] => len = %3d tok type = %d content = |%s| to exp = %d \n", toks->index, toks->len, toks->type, toks->content, toks->to_expand);
		toks = toks->next;
		ind++;
	}
	i++;
}

while (toks->index != 0)
	toks = toks->prev;
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
	// char **tab;
	// tab = malloc(8 * sizeof(char *));
	int i = 0;
	// while (i < 5)
	// {
	// 	tab[i] = malloc(20 * sizeof(char));
	// 	i++;
	// }
	// tab[0] = "echo";
	// tab[1] = "\"je suis    bete \"";
	// tab[2] = "|";
	// tab[3] = "$var";
	// tab[4] = "<";
	// tab[5] = "\'cette variable $lol pas interpretee\'  ";
	// tab[6] = "\" mais cette var $ici oui \" ";
	// tab[7] = NULL;

	i = -1;
	// while (argv[++i])
	// 	printf("[%d] => |%-s|\n", i, argv[i]);

	if (argc > 2)
	{
		printf("Only one str pls \n");
		exit(0);
	}

	tokenize(argv[1], &toks);
	//remove_toks_quotes(&toks);
}

// 	if (tok[OP][to_tokenize[i][j]])
// 	{
// 		printf ("COUCOU %c\n\n", to_tokenize[i][j]);
// 		toks->content = ft_substr(to_tokenize[i], 0, j);
// 		toks->index = i;
// 		toks->type = tok[OP][to_tokenize[i][j]];
// 		toks->len = strlen(toks->content);
// 		toks->next = malloc(sizeof(t_token));
// 		toks->next->prev = toks;
// 		toks = toks->next;
// 	}
// 	j++;
// }
// // if (strlen(to_tokenize[i]) == 1 && tok[OP][to_tokenize[i][j]])
// // 	toks->type = tok[OP][to_tokenize[i][j]];
// // else
// toks->content = strdup(to_tokenize[i]);
// 	toks->type = tok[WORD][to_tokenize[i][j]];
// if (strchr(toks->content, '$') && to_tokenize[i][0] != SQUOTE)
// 	toks->to_expand = TRUE;

// toks->index = i;
// toks->len = strlen(toks->content);
// printf("[%d] => len = %3d tok type = %d content = |%s| to exp = %d \n", toks->index, toks->len, toks->type, toks->content, toks->to_expand);
// i++;
// if (to_tokenize[i] == NULL)
// 	toks->next = NULL;
// else {
// 	toks->next = malloc(sizeof(t_token));
// 	toks->next->prev = toks;
// 	toks = toks->next;
// }
// printf ("previous token index = %d \n", toks->prev->index);
