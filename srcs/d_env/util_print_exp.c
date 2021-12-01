/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_print_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:21:28 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/01 14:11:36 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * in export the argument is a="b"
 * so we have to print this 
 */

int	init_strdup(int *i, int *k, char **fi, char *str)
{
	*i = 0;
	*k = 0;
	*fi = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (*fi == NULL)
	{
		perror("malloc failed");
		return (-1);
	}
	return (0);
}

char	*fill_thetab(char *str, char *fi, int i, int k)
{
	while (str[i] != '=')
	{
		fi[k] = str[i];
		k++;
		i++;
	}
	if (str[i] == '=')
	{
		fi[k] = '=';
		k++;
		i++;
	}
	fi[k] = '"';
	k++;
	while (str[i])
	{
		fi[k] = str[i];
		i++;
		k++;
	}
	fi[k] = '"';
	k++;
	fi[k] = '\0';
	return (fi);
}

char	*ft_strdup_cote(char *str)
{
	int		i;
	int		k;
	char	*fi;

	if (init_strdup(&i, &k, &fi, str) == -1)
		return (NULL);
	fi = fill_thetab(str, fi, i, k);
	return (fi);
}

/*
 * to fill my tab with the var of the export
 */

int	error_mall(t_env *env, char ***exp)
{
	int	i;

	i = nb_export(env);
	*exp = malloc(sizeof(char *) *(i + 1));
	if (*exp == NULL)
	{
		perror("malloc failed");
		return (-1);
	}
	return (0);
}

char	**fill_thexport(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**exp;

	tmp = env;
	if (error_mall(env, &exp) == -1)
		return (NULL);
	i = 0;
	while (tmp)
	{
		if ((tmp->visible == 0 || tmp->visible == 1))
		{
			if (ft_isin('=', tmp->env) == 0)
				exp[i] = ft_strdup(tmp->env);
			else
				exp[i] = ft_strdup_cote(tmp->env);
			if (exp[i] == NULL)
				return (free_tab_index(exp, i));
			i++;
		}
		tmp = tmp->next;
	}
	exp[i] = 0;
	return (exp);
}
