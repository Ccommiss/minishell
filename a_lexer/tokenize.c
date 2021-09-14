/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:37:27 by ccommiss          #+#    #+#             */
/*   Updated: 2021/09/14 19:00:24 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int tokenize(char **argv)
{
	char **tokens;
	char operators[] = "|<>&"

	tokens = ft_split(argv, " ");
	

}
