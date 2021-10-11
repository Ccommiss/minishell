#include "minishell.h"

void	ft_print_error(int err_number)
{
	printf("%s\n", strerror(err_number));
}
