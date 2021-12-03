/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:18:45 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/03 16:52:54 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_program(t_cmd *cmd, t_token *toks, char *str, void *stuff)
{
	if (stuff)
		free(stuff);
	cleanup(cmd, toks, str);
	if (stuff)
		free(stuff);
	exit (1);
}
