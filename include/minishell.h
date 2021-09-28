#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
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
enum tokens
{
	OP = 0,
	WORD = 1,
	QUOTE = 2,
	VAR = 3,
	TOK_EAT = 404,
	TOK_WORD = 100,
	TOK_PIPE,
	TOK_GREAT,
	TOK_LESS,
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
	t_cmd *next;
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




#endif
