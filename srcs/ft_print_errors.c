#include "minishell.h"

void	ft_print_error(char *arg, int err_number)
{
	if (
		printf("minishell: %s: %s\n", strerror(err_number));
	
}
