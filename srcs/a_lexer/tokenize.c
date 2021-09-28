/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:50:39 by ccommiss          #+#    #+#             */
/*   Updated: 2021/09/27 12:57:19 by ccommiss         ###   ########.fr       */
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

static int tok[2][255] = {
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

//void tokenize(char *to_tokenize, t_token *toks)
{
	int i;
	int j = 0;

	i = 0;
	j = 0;

	printf("\nDEBUG TOKENIZATION\n");
	while (to_tokenize[i])
	{
		toks->content = strdup(to_tokenize[i]);
		toks->to_expand = FALSE;
		j = 0;

		if (strlen(to_tokenize[i]) == 1 && tok[OP][to_tokenize[i][j]])
			toks->type = tok[OP][to_tokenize[i][j]];
		else
			toks->type = tok[WORD][to_tokenize[i][j]];
		if (strchr(toks->content, '$') && to_tokenize[i][0] != SQUOTE)
			toks->to_expand = TRUE;

		toks->index = i;
		toks->len = strlen(toks->content);
		printf("[%d] => len = %3d tok type = %d content = |%s| to exp = %d \n", toks->index, toks->len, toks->type, toks->content, toks->to_expand);
		i++;
		if (to_tokenize[i] == NULL)
			toks->next = NULL;
		else {
			toks->next = malloc(sizeof(t_token));
			toks->next->prev = toks;
			toks = toks->next;
		}
		printf ("previous t§oken index = %d \n", toks->prev->index);
	}

	while (toks->index != 0)
		toks = toks->prev;
}



void	remove_toks_quotes(t_token *toks)
{
	while (toks)
	{
		printf ("%d \n", toks->index);
		if (toks->content[0] == SQUOTE)
			toks->content = ft_strtrim(toks->content, "'");
		else if (toks->content[0] == DQUOTE)
			toks->content = ft_strtrim(toks->content, "\"");
		printf ("trimmed :%s \n", toks->content);
		toks = toks->next;
	}
}

// int main(int argc, char **argv)
// {

// 	t_token toks;
// 	// char **tab;
// 	// tab = malloc(8 * sizeof(char *));
// 	int i = 0;
// 	// while (i < 5)
// 	// {
// 	// 	tab[i] = malloc(20 * sizeof(char));
// 	// 	i++;
// 	// }
// 	// tab[0] = "echo";
// 	// tab[1] = "\"je suis    bete \"";
// 	// tab[2] = "|";
// 	// tab[3] = "$var";
// 	// tab[4] = "<";
// 	// tab[5] = "\'cette variable $lol pas interpretee\'  ";
// 	// tab[6] = "\" mais cette var $ici oui \" ";
// 	// tab[7] = NULL;

// 	i = -1;
// 	while (argv[++i])
// 		printf("[%d] => |%-s|\n", i, argv[i]);

// 	tokenize(argv, &toks);
// 	remove_toks_quotes(&toks);
// }
