/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:41:15 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/01 14:17:24 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env(t_env *env)
{
	void	*tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		free(env->env);
		tmp = env->next;
		free(env);
		env = tmp;
	}
}
