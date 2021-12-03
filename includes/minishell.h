#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"
# include "color.h"
# include "enums.h"
# include "structs.h"

extern int	g_return_value;

/*
**
**									[LEXER]
**
*/

/*
** init_funcs.c tokenizer.c, lex_error_detector.c, create_tokens_funcs.c
*/
void		init_tok_and_cmd(t_token *toks, t_cmd *cmd);
void		init_lexer_struct(t_lex *lex, char *to_tokenize, int save_exp);
void		tokenize(char *to_tokenize, t_token *toks, t_env *env);
int			fill_token_buff(t_lex *l, char **to_tokenize, int *i, t_env *env);
void		save_and_reset_context(int *old_context, t_lex **l);
void		syntax_error_detector(t_token *toks, int last_tok_is_op);
enum tokens	error_tab(int type);
void		debug_tokens(t_token *toks);
void		create_token(t_token **toks, t_lex *l);
int			create_exp_err_token(char **to_tokenize, int *i, t_lex *l);

/*
** context.c
*/
enum tokens	corresp(int c);
enum tokens	tok(int x, int y);
enum tokens	op_toks(int c);
enum tokens	word_toks(int c);
enum tokens	expand_toks(int c);

/*
** expand.c, valid_expand_char_tab.c
*/
int			handle_expand(char **to_tokenize, int *i, t_lex *l, t_env *env);
int			expand_substitution_error_detector(char *var_name, int exception);
char		*ft_str_replace(char *str, int start, int len, t_lex **l);
int			expand(char **to_tokenize, int *i, t_lex **lex, t_env *env);
int			is_valid_expand_char(int *exception, int c, int j);

/*
** quotes.c
*/
void		handle_quoted_context(int *context, int *i, char *to_tokenize);

/*
**	lex_error_detector.c
*/
int			expand_substitution_error_detector(char *var_name, int exception);
int			print_expand_errors(int error_type, char *var_name, char *trimmmed);
void		syntax_error_detector(t_token *toks, int last_tok_is_op);

/*
**
**								[PARSER]
**
*/

void		token_to_cmds(t_cmd *cmd, t_token *toks);
void		redirect(t_cmd *cmd, t_token **toks, int type, int len);
void		debug_cmds(t_cmd *cmds);
void		find_path(t_cmd *cmds, t_env *env);
int			syn_err_or_no_tok(t_cmd *cmd, t_token *toks);
int			check_syn_err(t_token *toks);
void		init_cmd(t_cmd *cmd);
void		command_and_suffix(t_cmd *cmd, t_token *toks, int *j);
void		free_command_items(t_cmd *cmd);

/*
**
**									[EXEC]
**
*/

/*
** cmd_to_exec.c
*/
void		cmd_to_exec(t_cmd *cmd, t_env *env, char *line);
void		set_status(int status, int process);
void		handle_signal(int state);

/*
**  ├─ Exec
**	|	├─ pipes_management
*/
int			do_the_pipe(t_cmd *cmd, t_env *env);
int			first_pid(t_cmd, t_env *env, int *pipefd, int nbr_p);
void		last_pid(t_cmd, t_env *env, int *pipefd, int nbr_p);
int			other_pid(t_cmd, t_env *env, t_pipe piped, int i);
int			nb_of_pipe(t_cmd *cmd);
int			malloc_of_pipe(t_cmd *cmd, t_pipe *piped);
void		close_all_p(int *fd, int nbr);
int			deploy_pipe(t_pipe piped);
int			which_redir(t_cmd cmd);
void		we_wait(pid_t *pid, int nbr_cmd, int *pipefd, int pipee);
void		exec_builtin(t_env *env, char **cmd, int builtin);

/*
**  ├─ Exec
**	|	├─ builtin_functions
*/
char		*get_pwd(void);
char		*strjoin_char(char *str, char *str1, char c);
int			is_home_unset(t_env *tmp, char *home);
int			cd(t_env *env, char **pwd);
void		set_thepwd(t_env *env);
int			check_echo(char *cmd_suffix);
int			count_double_tab(char **tab);
int			do_echo(char **cmd_suffix);
void		exito(char **cmd_suffix, t_cmd *cmd, t_env *env, char *line);
void		exit_p(char **cmd_suffix);
int			error_chdir(char *str, char *home, char *pwd);
int			no_home(char *home);
char		*strjoin_char(char *str, char *str1, char c);
int			set_the_oldpwd(t_env *tmp, char *home);
int			if_num(char *str);
void		error_num(char *str, t_env *env, int param);
int			error_count(char *str, t_env *env, int param);

/*
**  ├─ Exec
**	|	├─ redirections
*/
int			is_a_builtin(char *cmd);
int			redir_in(t_env *env, t_cmd cmd, char *line);
int			simple_redir_o(t_env *env, t_cmd cmd, char *line);
int			there_is_redir(t_env *env, t_cmd cmd, char *line);
int			both_redir(t_env *env, t_cmd cmd, char *line);
int			fill_thefd(t_cmd cmd);
void		here_doc(t_env *env, t_cmd cmd, int fd);
int			no_cmd(int fd, int error);
int			no_cmd_d(int fd, int fd1, int error);
int			fork_fail(char *str, int fd, char **tenvp);
int			fork_fail_d(char *str, int in, int out, char **tenvp);
void		ft_execve(char *path, char **cmd, char **tenvp);
int			redir_in_built(t_env *env, t_cmd cmd, int builtin, char *line );
int			redir_out_built(t_env *env, t_cmd cmd, int builtin, char *line);
int			redir_double_built(t_env *env, t_cmd cmd, int builtin, char *line);
void		built(t_env *env, t_cmd cmd, int *value, int builtin);
int			fd_neg(int *fd);
void		plus_plus(int *i, int *here_word, int fd);

/*
**
**									[ENV]
**
*/

int			printf_the_env(t_env *envp, char **cmd);
void		get_the_env(t_env **envp, char **env);
int			export_the_var(t_env *env, char *cmd_suffix);
int			remplace_the_var(t_env *env, char *cmd_suffix);
char		**ft_split_one_egal(char *str);
t_env		*ft_lstlastenv(t_env *lst);
void		ft_lstadd_backenv(t_env **alst, t_env *nev);
t_env		*ft_lstenv(char *content);
t_env		*ft_lstenv_inv(char *content);
int			need_to_unset(t_env *env, char *cmd_suffix);
int			delete_the_node(t_env **env, t_env *del);
int			unset_the_var(t_env *env, char *cmd_suffix);
int			check_the_cmd(char *cmd_suffix);
int			do_the_unset(t_env *env, char **cmd_suffix);
char		**list_to_cmd(t_env *env);
int			export_the(t_env *env, char **cmd_suffix);
void		ft_charswap(char **a, char **b);
char		*ft_strdup_cote(char *str);
int			nb_export(t_env *env);
char		**fill_thexport(t_env *env);
int			parse_cmd_suf(char *str);
int			ft_parse_concate(char *cmd_suffix);
int			print_the_export(t_env *env);
char		**free_tab_index(char **tab, int i);
int			case_first(t_env *tmp);
int			find_value_egal(char *cmd);

/*
**
**									[UTILS]
**
*/
void		clean_env(t_env *env);
void		free_cmds(t_cmd *cmd);
void		free_toks(t_token *toks);
void		cleanup(t_cmd *cmd, t_token *toks, char *line);
void		ft_print_error(char *arg);
void		ft_exit_program(t_cmd *cmd, t_token *toks, char *str, void *stuff);
int			check_quote(char *line);
int         line_length(char *line);
int         free_and_return(void *stuff, int ret);

#endif
