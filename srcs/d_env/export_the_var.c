/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_the_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:23:21 by mpochard          #+#    #+#             */
/*   Updated: 2021/09/24 18:50:08 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_the_var(t_env **env, char *cmd_suffix)
{
	int	i;

	i = 0;
	while(cmd_suffix[i])
	{
		if (cmd_suffix[i] == '=')
		{

	)
