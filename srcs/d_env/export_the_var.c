/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_the_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:23:21 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/28 14:11:33 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_the_var(t_env **env, char *cmd_suffix)
{
	int	i;

	i = 0;
	while(cmd_suffix[i])
	{
		if (cmd_suffix[i] == '=')
		{

	)