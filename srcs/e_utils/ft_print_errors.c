#include "minishell.h"

void	ft_print_error(char *arg)
{
	if (arg != NULL)
		printf("minishell: %s: %s\n", arg, strerror(errno));
	else
		printf("minishell: %s\n", strerror(errno));
}
