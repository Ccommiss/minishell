
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

	//printf ("VAR NAME = |%s| s: %d -- len : %d \n", str, start+1, len);
	if (str[start + 1] == '{') // on enleve les braces
		var_name = ft_substr(str, start + 2, len - 2); // recup la name var
	else
		var_name = ft_substr(str, start + 1, len); // recup la name var
	//printf ("VAR NAME = |%s|\n", var_name);
	while (env && ft_strncmp(var_name, env->key, ft_strlen(env->key) + 1) != 0)
		env = env->next;
	if (ft_strncmp(var_name, "?", 1) == 0) //si on demande le retour
		value = ft_itoa(return_value);
	else if (env == NULL)
		value = ft_strdup(""); 
	else
		value = ft_strdup(env->value);
	tmp = ft_substr(str, 0, start); //ce qui y avait avant
	new_str = ft_strconcat(tmp, value, start + ft_strlen(value));
	free(tmp);
	tmp = ft_strdup(new_str);
	free(new_str);
	new_str = ft_strconcat(tmp, str + start + len + 1,
		ft_strlen(tmp) + ft_strlen(str + start + len));
	free(tmp);
	return (new_str);
}

/*
** 	Expand finds the var name to tokenize in the user input and send it
**	to be replaced.
*/



int 	handle_error_inside(char *var_name, int brace)
{
	char	*trimmed_var;

	if (brace == 1)
	{
		printf ("%s : brace error, please close them\n", var_name);
		free(var_name);
		return (-1);
	}
	if (brace == 2)
	{
		trimmed_var = ft_substr(var_name, 2, ft_strlen(var_name) - 3);
		//printf ("trimmed var = %s\n", trimmed_var);
	}
	else
		trimmed_var = ft_substr(var_name, 1, ft_strlen(var_name) - 1);
	if (!ft_isalnum_str(trimmed_var) && ft_strncmp(trimmed_var, "?", 2) != 0)
	{
		printf ("%s : bad substitution\n", var_name);
		free(var_name);
		return (-1);
	}
	return (0);
}



static int is_valid_expand_char(int *brace, int c, int j)
{
	//printf ("%c %d\n", c, *brace);
	static int valid_tab[256] =
	{
		['A'...'Z'] = 1,
		['a'...'z'] = 1,
		['1'...'9'] = 1,
		['{'] = 1,
		['}'] = 1,
		['$'] = 1,
		['?'] = 1
	};
	if (j == 1 && c == '?')
		*brace = 3; //test
	if (j == 1 && c == '{')
		*brace = 1;
	if (*brace == 0 && ((j > 0 && c == '$') || (j > 1 && c == '{')) ) //je crois 
	{
		//printf("newvar\n");
		return (0);
	}
	if (*brace == 0)
		return (valid_tab[c]);
	if (*brace == 1 && c == '}')
	{
		*brace = 2;
		return (0);
	}
	if (*brace == 1 && ft_isascii(c))
		return (1);

	return (0);
}

int	expand(char **to_tokenize, int *i, int *context, t_env *env)
{
	int		j;
	int		brace; // va servir aussi si ? 
	char	*var_name;

	j = 0;
	brace = 0;
	while (to_tokenize[0][*i+j] && is_valid_expand_char(&brace, to_tokenize[0][*i+j], j) && brace != 3)
		j++;
	if (brace == 2 || brace == 3)
		j++;
	var_name = ft_substr(*to_tokenize, *(i),  j); // recup la name var verifier erreurs ici
	if (j > 1) // si on a plus que juste le $
		*to_tokenize = ft_str_replace(*to_tokenize, *i, j - 1, env);
	handle_quoted_context(context, i, *to_tokenize);
	return (handle_error_inside (var_name, brace));
}
