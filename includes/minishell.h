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


int return_value; //globale 

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

enum signal_location
{
	MAIN_PROCESS,
	CHILD,
	CHILD_HANDLING
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
	TOK_ERR,
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


/* d_env
 * the file for put env in a list chaine or for display this list chainee
 */
void	printf_the_env(t_env *envp);
void	get_the_env(t_env **envp, char **env);
int		export_the_var(t_env *env, char *cmd_suffix);
int		remplace_the_var(t_env *env, char *cmd_suffix);
char	**ft_split_one_egal(char *str);
t_env *ft_lstlastenv(t_env *lst);
void	ft_lstadd_backenv(t_env **alst, t_env *nev);
t_env	*ft_lstenv(char *content);
int	need_to_unset(t_env *env, char *cmd_suffix);
void	delete_the_node(t_env **env, t_env *del);
int	unset_the_var(t_env *env, char *cmd_suffix);
void	check_the_cmd(char *cmd_suffix);
void	do_the_unset(t_env *env, char **cmd_suffix);
/*
 * END OF D_ENV
 * */

/* e_builtin
 */
char	*get_pwd(void);
char	*strjoin_char(char *str, char *str1, char c);
int		is_home_unset(t_env *tmp, char *home);
void	cd(t_env *env, char *pwd);
void	set_thepwd(t_env *env);
int		check_echo(char *cmd_suffix);
int		count_double_tab(char **tab);
void	do_echo(char **cmd_suffix);
/*
 * f_redirection
 * */
void	cmd_to_exec(t_cmd *cmd, t_env *env);
int		is_a_builtin(char *cmd);
void	redir_in(t_env *env, char **cmd, int fd);
void	simple_redir_o(t_env *env, int fd, char **cmd);
int		there_is_redir(t_env *env, t_cmd cmd);
void	both_redir(t_env *env, char **cmd, int in, int out);
int		fill_thefd(t_cmd cmd);
void	here_doc(t_env *env, t_cmd cmd , int fd);
/* end of f_redir*/



/*
** Lexer
*/
void		tokenize(char *to_tokenize, t_token *toks, t_env *env);
void		init_token(t_token *toks);
char		*ft_str_replace(char *str, int start, int len, t_env *env);
void		debug_tokens(t_token *toks);

int			expand(char **to_tokenize, int *i, int *context, t_env *env);
void		handle_quoted_context(int *context, int *i, char *to_tokenize);
enum tokens op_toks(int c);
enum tokens word_toks(int c);
enum tokens quote_toks(int c);

/*
** Parser
*/

t_cmd		*token_to_cmds(t_cmd *cmd, t_token *toks);
void		redirect(t_cmd *cmd, t_token **toks, int type, int len);
void		debug_cmds(t_cmd *cmds);
void		find_path(t_cmd *cmds, t_env *env);

void	handle_signal(int state);
void 	set_status(int status);


void 	quithandler();
void 	quithandler2();








#endif
