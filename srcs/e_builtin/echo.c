#include "../../include/minishell.h"

/*
 * cmd_suffix is the -n
 */
int	check_echo(char *cmd_suffix)
{
	int	i;

	i = 0;
	if (cmd_suffix[i] == '-')
		i++;
	else
		return (0);
	while (cmd_suffix[i] == 'n')
		i++;
	if (cmd_suffix[i] != 'n' && cmd_suffix[i] != '\0')
		return (0);
	else
		return (1);
	return (0);
}

int		count_double_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	do_echo(char **cmd_suffix)
{
	int	i;
	int	count;

	i = 0;
	count = count_double_tab(cmd_suffix);
	if (check_echo(cmd_suffix[i]) == 1)
	{
		i++;
		if (count > 2)
		{
		while (cmd_suffix[i])
		{
			write(1, cmd_suffix[i], ft_strlen(cmd_suffix[i]));
			i++;
		}
	}
	}
	else
	{
		if (count > 1)
		{
		while (cmd_suffix[i])
		{
			write(1, cmd_suffix[i], ft_strlen(cmd_suffix[i]));
			i++;
		}
		}
		write(1, "\n", 1);
	}
}
