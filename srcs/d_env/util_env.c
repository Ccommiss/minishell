/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:11:13 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/07 17:07:09 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_one_egal(char *str)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) *(2 + 1));
	if (tab == NULL)
		return (NULL);
	while ((ft_isalnum(str[i]) == 1 || str[i] == '_') && str[i] != '=')
		i++;
	tab[j] = ft_strndup(str, i);
	j++;
	if (str[i] == '+')
		i++;
	if (str[i] == '=')
		i++;
	tab[j] = ft_strdup(&str[i]);
	j++;
	tab[j] = 0;
	return (tab);
}

static	void	init(int *i, int *k)
{
	*i = 0;
	*k = 0;
}

char	*ft_strjoin_char(char *str, char *str1, char c)
{
	int		i;
	int		j;
	int		k;
	char	*fi;

	init(&i, &k);
	j = ft_strlen(str) + ft_strlen(str1) + 1;
	fi = malloc(sizeof(char *) * (j + 1));
	if (!(fi))
		return (NULL);
	while (str[i])
	{
		fi[i] = str[i];
		i++;
	}
	fi[i] = c;
	i++;
	while (str1[k])
	{
		fi[i] = str1[k];
		k++;
		i++;
	}
	fi[i] = '\0';
	return (fi);
}
