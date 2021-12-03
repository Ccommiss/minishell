#ifndef STRUCTS_H
# define STRUCTS_H

# include "libs.h"


/*
 *	s_env structure
 */
typedef struct	s_env
{
	char	*key;
	char	*value;
	char	*env;
	int		visible;
	struct	s_env *next;
	struct	s_env *prev;
}				t_env;

/*
** s_lex struct
**
** 	- token : buffer to fill for current token
**	- buf_i : index of char for token buffer
**	- context : context to interpret char (single quote,
**		double quote, or word)
**	- ref_char : token type of the first char of the token
**	- exp_res : result of expand
*/
typedef struct s_lex t_lex;
typedef struct s_lex
{
	char	token[2048];
	int		buf_i;
	int		context;
	int		ref_char;
	int		exp_res;
	int		exp_len;
	int		old_context;
	t_env	**env;
}t_lex;


typedef struct s_token t_token;
typedef struct s_token
{
	char *content;
	int type;
	int index;
	int len;

	t_token *next;
	t_token *prev;
} 				t_token;

typedef struct s_cmd t_cmd;
typedef struct s_cmd
{
	int 	index;
	char 	*cmdp; //le path
	char 	**cmd_args;
	int		test;
	int 	io_in; //fd entree commande
	int 	dless; // <<
	char	 **io_here;
	int 	here_words; //compte le nb de io_here pour faire io_here[here_words]
	int 	io_out; //fd sortie commande
	int 	dgreat; // >>
	int 	error;

	t_cmd 	*next;
	t_cmd 	*prev;
}t_cmd;


typedef struct s_arg
{
	int s_quote;
	int d_quote;
	int nb_pipe;
} t_arg;


/*
 *	s_pipe struct
 */
typedef struct s_pipe
{
	int		i;
	int		*pipefd;
	pid_t	*pid;
	int		nbr_cmd;
	int		nbr_p;
	int		status;
	int		temp;
}				t_pipe;

#endif
