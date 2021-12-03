/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:52:19 by ccommiss          #+#    #+#             */
/*   Updated: 2021/12/03 16:52:21 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *arg)
{
	if (arg != NULL)
		printf("minishell: %s: %s\n", arg, strerror(errno));
	else
		printf("minishell: %s\n", strerror(errno));
}
