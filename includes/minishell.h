#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "color.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"


// typedef struct s_utils {

// 	int return_value; //globale
// 	int g_sig;
// }				t_utils;
// extern t_utils g_utils;
extern int return_value;
extern int process;

typedef struct s_arg
{
	int s_quote;
	int d_quote;
	int nb_pipe;
} t_arg;


enum bool
{
	ERROR = -1,
	BREAK = -1,
	FALSE,
	TRUE
};

enum io {
	NOT_SPECIFIED = -100
};

enum signal_location
{
	MAIN_PROCESS,
	CHILD,
	CHILD_HANDLING,
	HEREDOC
};

enum expand
{
	NO_BRACE,
	OPEN_BRACE = 1,
	CLOSE_BRACE = 2,
	DOL_OR_QUEST = 3
};


/*
**	Enum mainly used in lexing for context purposes
**
**	Nb. we need to differentiate :
**		- TOK_ERR : meaning a bad substitution error, that prevents
**			the current cmd to be executed
**		- TOK_NO_VAR : meaning a $ that did not match any key in env,
**			resulting in NULL
**		- SYNT_ERR : syntax error preventing the whole cmd line to be executed
*/
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
	TOK_ERR, // bad substitu erreur
	TOK_NO_VAR, //expand but var doesnt exist $fkjahf
	SYNT_ERR, //erreur builtin syntax
	SQUOTE = '\'',
	DQUOTE = '\"'
};

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
}	t_lex;


typedef struct s_token t_token;
typedef struct s_token
{
	char *content;
	int type;
	int index;
	int len;

	t_token *next;
	t_token *prev;
} t_token;

typedef struct s_cmd t_cmd;
typedef struct s_cmd
{
	int index;
	char *cmdp; //le path
	char **cmd_args;
	int		test;
	int io_in; //fd entree commande
	int dless; // <<
	char **io_here;
	int here_words; //compte le nb de io_here pour faire io_here[here_words]
	int io_out; //fd sortie commande
	int dgreat; // >>
	int error;

	t_cmd *next;
	t_cmd *prev;
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
	int		visible;
	struct	s_env *next;
	struct	s_env *prev;
}				t_env;
/*
 * struct for the pipe bc 4 args in fct is too light
 */
typedef struct s_pipe
{
	int		i;
	int		*pipefd;
	pid_t	*pid;
	int		nbr_cmd;
	int		nbr_p;
}				t_pipe;

/* d_env
 * the file for put env in a list chaine or for display this list chainee
 */
int		printf_the_env(t_env *envp, char **cmd);
void	get_the_env(t_env **envp, char **env);
int		export_the_var(t_env *env, char *cmd_suffix);
int		remplace_the_var(t_env *env, char *cmd_suffix);
char	**ft_split_one_egal(char *str);
t_env *ft_lstlastenv(t_env *lst);
void	ft_lstadd_backenv(t_env **alst, t_env *nev);
t_env	*ft_lstenv(char *content);
t_env	*ft_lstenv_inv(char *content);
int	need_to_unset(t_env *env, char *cmd_suffix);
void	delete_the_node(t_env **env, t_env *del);
int	unset_the_var(t_env *env, char *cmd_suffix);
int		check_the_cmd(char *cmd_suffix);
int		do_the_unset(t_env *env, char **cmd_suffix);
char	**list_to_cmd(t_env *env);
int		export_the(t_env *env, char **cmd_suffix);
void	ft_charswap(char **a, char **b);
char	*ft_strdup_cote(char *str);
int		nb_export(t_env *env);
char	**fill_thexport(t_env *env);
int		parse_cmd_suf(char *str);
int		ft_parse_concate(char *cmd_suffix);
int		print_the_export(t_env *env);
char	**free_tab_index(char **tab, int i);

/*
 * END OF D_ENV
 * */

/* e_builtin
 */
char	*get_pwd(void);
char	*strjoin_char(char *str, char *str1, char c);
int		is_home_unset(t_env *tmp, char *home);
int		cd(t_env *env, char *pwd);

void	set_thepwd(t_env *env);
int		check_echo(char *cmd_suffix);
int		count_double_tab(char **tab);
int		do_echo(char **cmd_suffix);
void	exito(char *str);
/*
 * f_redirection
 * */
void	cmd_to_exec(t_cmd *cmd, t_env *env);
int		is_a_builtin(char *cmd);
int		redir_in(t_env *env, t_cmd cmd, int fd, char *path);
int		simple_redir_o(t_env *env, int fd, t_cmd cmd, char *ath);
int		there_is_redir(t_env *env, t_cmd cmd);
int		both_redir(t_env *env, t_cmd cmd, int in, int out);
int		fill_thefd(t_cmd cmd);
void	here_doc(t_env *env, t_cmd cmd , int fd);
int		no_cmd(int fd, int error);
int		no_cmd_d(int fd, int fd1, int error);
int		fork_fail(char *str, int fd, char **tenvp);
int		fork_fail_d(char *str, int in, int out,  char **tenvp);
void	ft_execve(char *path, char **cmd, char **tenvp);
int		redir_in_built(t_env *env, char **cmd, int fd , int builtin);
int		redir_out_built(t_env *env, char **cmd, int fd , int builtin);
int		redir_double_built(t_env *env, t_cmd cmd, int builtin);
/* end of f_redir*/

/*
 * g_pipe
 */
int	do_the_pipe(t_cmd *cmd, t_env *env);
int		first_pid(t_cmd, t_env *env, int *pipefd, int nbr_p);
void		last_pid(t_cmd, t_env *env, int *pipefd, int nbr_p);
int		other_pid(t_cmd, t_env *env, int *pipefd, int i, int nbr_p);
int		nb_of_pipe(t_cmd *cmd);
int		malloc_of_pipe(t_cmd *cmd, int **pipefd, pid_t **pid, int *nbr_cmd);
void	close_all_p(int *fd, int nbr);
int		deploy_pipe(int *pipefd, pid_t *pid, int nbr_cmd, int nbr_p);
int		which_redir(t_cmd cmd);
void	we_wait(pid_t *pid, int nbr_cmd, int *pipefd, int pipee);
void	exec_builtin(t_env *env, char **cmd, int builtin);
/*
**									[LEXER]
*/

/*
** tokenizer.c, lex_error_detector.c
*/

void		init_tok_and_cmd(t_token *toks, t_cmd *cmd);
void		tokenize(char *to_tokenize, t_token *toks, t_env *env);
void 		syntax_error_detector(t_token *toks, int last_tok_is_op);
int			expand_substitution_error_detector(char *var_name, int exception);
enum tokens error_tab(int type);
void debug_tokens(t_token *toks);

/*
** context.c
*/

enum tokens corresp(int c);
enum tokens	tok(int x, int y);
enum tokens op_toks(int c);
enum tokens word_toks(int c);
enum tokens quote_toks(int c);

/*
** expand.c
*/
char		*ft_str_replace(char *str, int start, int len, t_env *env);
int			expand(char **to_tokenize, int *i, int *context, t_env *env);
void		handle_quoted_context(int *context, int *i, char *to_tokenize);

void ft_print_error(char *arg);

/*
** quotes.c
*/
void handle_quoted_context(int *context, int *i, char *to_tokenize);


/*
** 									[PARSER]
*/

t_cmd		*token_to_cmds(t_cmd *cmd, t_token *toks);
void		redirect(t_cmd *cmd, t_token **toks, int type, int len);
void		debug_cmds(t_cmd *cmds);
void		find_path(t_cmd *cmds, t_env *env);

void	handle_signal(int state);
void 	set_status(int status, int process);


void 	quithandler();
void 	quithandler2();


/*
**	utils.c
*/
void cleanup(t_cmd *cmd, t_token *toks, char *line);
void free_toks(t_token *toks);
void free_cmds(t_cmd *cmd);

#endif
