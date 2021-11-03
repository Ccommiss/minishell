/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_the_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:23:21 by mpochard          #+#    #+#             */
/*   Updated: 2021/10/20 11:14:21 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*'
 * on parse le cmd_suffix pour savoir si il y a un = et on split dessus
 */
int	nb_export(t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		if (env->visible == 0 || env->visible == 1)
		{
			i++;
		}
		env = env->next;
	}
	return (i);
}
char	*ft_strdup_cote(char *str)
{
	int		i;
	int		k;
	char	*fi;

	i = 0;
	k = 0;
	fi = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!(fi))
		return (NULL);
	while (str[i] != '=')
	{
		fi[k] = str[i];
		k++;
		i++;
	}
	if(str[i] == '=')
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
	fi[k]= '"';
	k++;
	fi[k] = '\0';
	return (fi);
}

int	export_the_var(t_env *env, char *cmd_suffix)
{
	int	i;

	i = 0;
	while (cmd_suffix[i])
	{
		if (cmd_suffix[i] == '=')
		{
			ft_lstadd_backenv(&env, ft_lstenv(cmd_suffix));
			return (0);
		}
		i++;
	}
	return (1);
}

char	**fill_thexport(t_env *env)
{
	int		i;
	t_env *tmp;
	char	**exp;
	
	tmp = env;
	i = nb_export(env);
	exp = malloc(sizeof(char *) * (i + 1));
	if ( exp == NULL)
	{
		perror("probleme with malloc");
		return (NULL);
	}
	i = 0;
	while (tmp)
	{
		if ( tmp->visible == 0 || tmp->visible == 1)
		{
			exp[i] = ft_strdup_cote(tmp->env);
			i++;
		}
		tmp = tmp->next;
	}
	exp[i] = 0;
	return (exp);
}

void	ft_charswap(char **a, char **b)
{
	char *c;

	c = *a;
	*a = *b;
	*b = c;
}

int	print_the_export(t_env *env)
{
	char	**exp;
	int		i;
	int		j;
	int		nbr;

	i = 0;
	exp = fill_thexport(env);
	if ( exp == NULL)
		return (-1);
	nbr = nb_export(env);
	while (i < nbr)
	{
		j = 0;
		while (j < nbr - 1 - i)
		{
			if (strcmp(exp[j], exp[j + 1]) > 0)
			{
				ft_charswap(&exp[j], &exp[j + 1]);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while ( exp[i])
	{
		printf("declare -x %s\n", exp[i]);
		i++;
	}
return (1);
}

int	export_visible(char *cmd_suffix, t_env *env)
{
	char	*cmd;

	cmd = ft_strdup(cmd_suffix);
	ft_lstadd_backenv(&env,ft_lstenv_inv(cmd));
	return (1);
}

int	remplace_the_var(t_env *env, char *cmd_suffix)
{
	int		i;
	t_env	*tmp;
	int		egal;
	char	**tab;

	i = 0;
	egal = 1;
	tmp = env;
	if (cmd_suffix == NULL)
		return (print_the_export(env));
	while(cmd_suffix[i])
	{
		if (cmd_suffix[i] == '=')
			break;
		i++;
	}
	if ( (size_t)i == ft_strlen(cmd_suffix))
			egal = 0;
	tab = ft_split_one_egal(cmd_suffix);
	while (env)
	{
		
		if (strcmp(env->key, tab[0]) == 0)
		{
			if (egal == 0)
				return (1);
			free(env->key);
			free(env->value);
			env->key = tab[0];
			env->value = tab[1];
			env->env = cmd_suffix;
			return (1);
		}
		env = env->next;
	}
	if (egal == 0)
		return (export_visible(cmd_suffix, tmp));
	return (0);
}
