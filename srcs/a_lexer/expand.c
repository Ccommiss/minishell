/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:19:09 by ccommiss          #+#    #+#             */
/*   Updated: 2021/10/06 14:52:15 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
**	ft_str_replace finds the value associated to the provided variable
**	key iterating through the env variable.
*/
char *ft_str_replace(char *str, int start, int len, t_env *env)
{
	char *var_name;
	char *new_str;
	char *value;
	char *tmp;

	var_name = ft_substr(str, start + 1, len); // recup la name var
	while (env && ft_strncmp(var_name, env->key, ft_strlen(env->key) + 1) != 0)
		env = env->next;
	if (env == NULL)
		value = ft_strdup("");
	else
		value = ft_strdup(env->value);
	tmp = ft_substr(str, 0, start);
	new_str = ft_strconcat(tmp, value, start + ft_strlen(value));
	free(tmp);
	tmp = ft_strdup(new_str);
	free(new_str);
	new_str = ft_strconcat(tmp, str + start + ft_strlen(var_name) + 1,
		ft_strlen(tmp) + ft_strlen(str) - (start + ft_strlen(var_name)));
	free(tmp);
	printf ("new stre |%s|\n", new_str);
	return (new_str);
}

/*
** 	Expand finds the var name to tokenize in the user input and send it
**	to be replaced.
*/
void	expand(char **to_tokenize, int *i, int *context, t_env *env)
{
	int j;

	j = 0;
	while (to_tokenize[0][*i+j] && to_tokenize[0][*i+j] != ' '
		&& to_tokenize[0][*i+j] != DQUOTE) //test le +1 pour pas envoyer lespace
	{
		printf (" test : %c - %c \n", to_tokenize[0][*i+j], to_tokenize[0][*i+j+1]);
			j++;
	}
	if (j > 1) // si on a plus que juste le $
		*to_tokenize = ft_str_replace(*to_tokenize, *i, j - *i, env);
	//printf ("to_tokenize = %s \n",);
	handle_quoted_context(context, i, *to_tokenize); // TEST

}
