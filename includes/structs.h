/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:35:35 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/03 17:39:24 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libs.h"

/*
** s_env_struct
*/

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*env;
	int				visible;
	struct s_env	*next;
	struct s_env	*prev;
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
}			t_lex;

typedef struct s_token
{
	char			*content;
	int				type;
	int				index;
	int				len;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

/*
**	s_cmd is the struct used to store all commands data.
**	- index : index of structure
**	- cmdp : path of command
**	- cmd_args : cmd + suffix
**	- io_in : file descriptor of in command ; set default to -1
**	- dless : if << is typed, set to TRUE
**	- io_here : contains delimiters of heredoc
**	- here_words : contains numbers of heredocs delimiters 
**	- io_out : file descriptor of out command ; set default to -1
**	- dgreat : if >> is typed, set to TRUE
**	- error : if error is TRUE, cmd is not executed but still contains next 
*/

typedef struct s_cmd
{
	int				index;
	char			*cmdp;
	char			**cmd_args;
	int				io_in;
	int				dless;
	char			**io_here;
	int				here_words;
	int				io_out;
	int				dgreat;
	int				error;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}			t_cmd;

/*
**	s_arg struct
*/

typedef struct s_arg
{
	int	s_quote;
	int	d_quote;
	int	nb_pipe;
}				t_arg;

/*
**	s_pipe struct
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
