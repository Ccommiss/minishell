#include "minishell.h"

void	ft_print_error(char *arg, int err_number)
{
	if (arg != NULL)
		printf("minishell: %s: %s\n", arg, strerror(err_number));
	
}
