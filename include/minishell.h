#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "../libft/libft.h"

typedef struct	s_arg
{
	int	s_quote;
	int	d_quote;
	int	nb_pipe;
}				t_arg;
#endif
