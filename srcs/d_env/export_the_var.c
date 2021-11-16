/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_the_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:23:21 by mpochard          #+#    #+#             */
/*   Updated: 2021/11/16 11:23:16 by mpochard         ###   ########.fr       */
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
		if ((env->visible == 0 || env->visible == 1))
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
		if ((tmp->visible == 0 || tmp->visible == 1))
		{
			if(ft_isin('=', tmp->env) == 0)
				exp[i] = ft_strdup(tmp->env);
			else
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
return (0);
}

int	export_visible(char *cmd_suffix, t_env *env)
{
	char	*cmd;

	cmd = ft_strdup(cmd_suffix);
	ft_lstadd_backenv(&env,ft_lstenv_inv(cmd));
	return (1);
}

int	parse_cmd_suf(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 1)
		i++;
	else
	{
		printf("export: « %s » : identifiant non valable\n", str);
		return (-1);
	}
	while (ft_isalnum(str[i]) == 1)
		i++;
	if (str[i] == '+' && str[i + 1] == '=')
		return (0);
	else if (str[i] == '=')
		return (0);
	else if (str[i] == '\0')
		return (0);
	else
	{
		printf("export: « %s » : identifiant non valable\n", str);
		return (-1);
	}
	return (0);
}

void	ft_concatene_exp(t_env *env, char **tab)
{
	char *temp;

	free(env->key);
	env->key = tab[0];
	temp = ft_strdup(env->value);
	free(env->value);
	env->value = ft_strjoin(temp, tab[1]);
	free(env->env);
	env->env = strjoin_char(env->key, env->value, '=');
	free(temp);
}

int	remplace(t_env *env, int egal, char *cmd_suffix)
{
	char	**tab;

	tab = ft_split_one_egal(cmd_suffix);
	if (tab == NULL)
	{
		perror("malloc failed\n");
		return (-1);
	}
	while (env)
	{
		if (strcmp(env->key, tab[0]) == 0)
		{
			if (egal == 0)
			{
				ft_free_double_tab(tab);
				return (1);
			}
			if (egal == 2)
			{
				ft_concatene_exp(env, tab);
				return (1);
			}
			if (env->visible == 1 && egal == 1)
				env->visible = 0;
			free(env->key);
			free(env->value);
			free(env->env); //new
			env->key = tab[0];
			env->value = tab[1];
			env->env = strjoin_char(tab[0], tab[1], '=');
			return (1);
		}
		env = env->next;
	}
	ft_free_double_tab(tab);
	return (0);
}
/*
 * egal 1  c'est qu'il a a=b
 * egal2 a+=b 
 * egal 0 a 
 *
 * */
int	ft_export_concate(char *cmd_suffix)
{
	int i;

	i= 0;
	while(cmd_suffix[i])
	{
		if (cmd_suffix[i] == '+')
			i++;
		if (cmd_suffix[i] == '=')
			return (1);
		i++;
	}
	return (0);
}


int	export_the(t_env *env, char	**cmd_suffix)
{
	int		k;
	int		egal;
	t_env	*tmp;
	int		error;

	tmp = env;
	k = 0;
	error = 0;
	if (count_double_tab(cmd_suffix) == 0)
		return(print_the_export(env));
	while(cmd_suffix[k])
	{
		if (parse_cmd_suf(cmd_suffix[k]) == -1)
		{
			error = -1;
			k++;
			if (cmd_suffix[k]== '\0')
				return (error);
			continue;
		}
		if (ft_export_concate(cmd_suffix[k]) == 1)
			egal = 2;
		else if (ft_isin('=', cmd_suffix[k]) == 1)
			egal = 1;
		else
			egal = 0;
		if (remplace(tmp,egal, cmd_suffix[k]) == 0)
		{
			if (egal == 1 || egal == 2)
				ft_lstadd_backenv(&env, ft_lstenv(cmd_suffix[k]));
			else if (egal == 0)
				ft_lstadd_backenv(&env, ft_lstenv_inv(cmd_suffix[k]));
		}
		k++;
	}
	return (error);
}
