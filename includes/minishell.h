#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "color.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_arg
{
	int s_quote;
	int d_quote;
	int nb_pipe;
} t_arg;


enum bool
{
	ERROR = -1,
	FALSE,
	TRUE
};

enum io{
	NOT_SPECIFIED = -100
};
enum tokens
{
	OP = 4,
	WORD = 1,
	QUOTE = 2,
	VAR = 3,
	TOK_EAT = 404,
	TOK_WORD = 100,
	TOK_PIPE,
	TOK_GREAT,
	TOK_LESS,
	TOK_EQUAL,
	SQUOTE = '\'',
	DQUOTE = '\"'
};

typedef struct s_token t_token;
typedef struct s_token
{
	char *content;
	int type;
	int index;
	int len;
	int to_expand;
	t_token *next;
	t_token *prev;
} t_token;

typedef struct s_cmd t_cmd;
typedef struct s_cmd
{
	int index;
	char *cmdp; //le path
	char **cmd_args;
	int io_in; //fd entree commande
	int dless; // <<
	int io_out; //fd sortie commande
	int dgreat; // >>

	t_cmd *next;
	t_cmd *prev;
	t_cmd *head;

} t_cmd;


typedef struct s_data
{
	char ***envp;  // stocke envuronnemebnt
	t_token *toks; // ptr sur la head de la liste chainee des tokens
	t_cmd *cmds;   // ptr sur la head de la liste chainee des commandes

} t_data;
/*
 * the struct for the env
 */
typedef struct	s_env
{
	char	*key;
	char	*value;
	char	*env;
	struct	s_env *next;
}				t_env;

/* d_env
 * the file for put env in a list chaine or for display this list chainee
 */
void	printf_the_env(t_env *envp);
void	get_the_env(t_env **envp, char **env);
void	export_the_var(t_env **env, char *cmd_suffix);
void	tokenize(char *to_tokenize, t_token *toks, t_env *env);
void	init_token(t_token *toks);
char	*ft_str_replace(char *str, int start, int len, t_env *env);
void	debug_tokens(t_token *toks);
void	debug_cmds(t_cmd *cmds);
void	expand(char **to_tokenize, int *i, int *context, t_env *env);
void	handle_quoted_context(int *context, int *i, char *to_tokenize);




t_cmd *token_to_cmds(t_cmd *cmd, t_token *toks);

enum tokens op_toks(int c);
enum tokens word_toks(int c);
enum tokens quote_toks(int c);








#endif
