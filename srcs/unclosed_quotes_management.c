/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes_management.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:22:54 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/02 16:22:55 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *line)
{
	int	i;
	int	context;

	i = 0;
	context = WORD;
	while (line[i])
	{
		if (context == WORD && line[i] == SQUOTE)
			context = SQUOTE;
		else if (context == WORD && line[i] == DQUOTE)
			context = DQUOTE;
		else if (context == SQUOTE && line[i] == SQUOTE)
			context = WORD;
		else if (context == DQUOTE && line[i] == DQUOTE)
			context = WORD;
		i++;
	}
	if (context != WORD)
	{
		printf ("Please check quotes and close them.\n");
		free (line);
		g_return_value = 1;
		return (ERROR);
	}
	return (0);
}
