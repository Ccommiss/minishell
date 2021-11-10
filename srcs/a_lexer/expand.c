#include "minishell.h"

/*
**	extract_pure_var_name : "purifies" var_name so it removes
**		- case 1 : $ symbole and {} both braces (eg: ${PATH} becomes PATH)
**		- case 2 : only $ symbol
*/
void extract_pure_var_name(char **var_name, int len, int start, char *str)
{
	if (str[start + 1] == '{')
		*var_name = ft_substr(str, start + 2, len - 2);
	else
		*var_name = ft_substr(str, start + 1, len);
	//free(str); MAUVAIS FREE QUI A TOUT CASSE
	printf("VAR NAME = |%s|\n", *var_name);
}

/*
**	assign_value : return "values" as the expanded var
**		- 1) handles 2 special cases : $$ and $?
**		- 2) iterates through the env to see if one
**			value match the provided key (var_name)
*/
char *assign_value(t_env *env, char *var_name)
{
	if (ft_strncmp(var_name, "?", 1) == 0) //si on demande le retour
		return (ft_itoa(return_value));
	else if (ft_strncmp(var_name, "$", 1) == 0) //si on demande le retour
		return (ft_itoa(getpid()));
	while (env && ft_strncmp(var_name, env->key, ft_strlen(env->key) + 1) != 0)
		env = env->next;
	if (env == NULL)
		return (ft_strdup(""));
	else
		return (ft_strdup(env->value));
}

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

	extract_pure_var_name(&var_name, len, start, str);
	value = assign_value(env, var_name);
	free(var_name);

	tmp = ft_substr(str, 0, start); //ce qui y avait avant
	new_str = ft_strconcat(tmp, value, start + ft_strlen(value));
	free(tmp);
	tmp = ft_strdup(new_str);
	free(new_str);
	new_str = ft_strconcat(tmp, str + start + len + 1,
						   ft_strlen(tmp) + ft_strlen(str + start + len));
	free(tmp);
	free(value);
	return (new_str);
}

/*
** 	Expand finds the var name to tokenize in the user input and send it
**	to be replaced.
*/

int handle_error_inside(char *var_name, int brace)
{
	char *trimmed_var;

	printf("brace %d \n", brace);
	if (brace == 1)
	{
		printf("%s : brace error, please close them\n", var_name);
		free(var_name);
		return (ERROR);
	}
	if (brace == 2)
		trimmed_var = ft_substr(var_name, 2, ft_strlen(var_name) - 3);
	else
		trimmed_var = ft_substr(var_name, 1, ft_strlen(var_name) - 1);
	if (!ft_isalnum_str(trimmed_var) && ft_strncmp(trimmed_var, "?", 2) != 0 && ft_strncmp(trimmed_var, "$", 2) != 0)
	{
		printf("%s \n", trimmed_var);
		printf("%s : bad substitution\n", var_name);
		return_value = 1;
		free(var_name);
		return (ERROR);
	}
	free(trimmed_var);
	free(var_name);
	return (0);
}

/*
** is_valid_expand_char test each of character to know if
**	1 - We are still in the expand context (no space) or
**		no followed by another var (another $var)
**	2 - In case of braces, if no 'bad substitution char'
**		is found inside
*/

static int is_valid_expand_char(int *brace, int c, int j)
{
	static int valid_tab[4][256] =
		{
			[NO_BRACE]['A' ... 'Z'] = 1,
			[NO_BRACE]['a' ... 'z'] = 1,
			[NO_BRACE]['1' ... '9'] = 1,
			[NO_BRACE]['{'] = 1,
			[OPEN_BRACE][0 ... 255] = 1,
			[CLOSE_BRACE]['}'] = 1,
			[DOL_OR_QUEST]['?'] = 1,
			[DOL_OR_QUEST]['$'] = 1,
		};
	static int set_exception[4][256] =
		{
			[NO_BRACE]['?'] = DOL_OR_QUEST,
			[NO_BRACE]['$'] = DOL_OR_QUEST,
			[NO_BRACE]['{'] = OPEN_BRACE,
			[OPEN_BRACE]['}'] = CLOSE_BRACE,
			[OPEN_BRACE]['$'] = DOL_OR_QUEST,
			[DOL_OR_QUEST]['$'] = NO_BRACE,
			[DOL_OR_QUEST]['}'] = CLOSE_BRACE,
		};
	if (j == 1 || c == '}' || (j > 1 && *brace == DOL_OR_QUEST)) 
		*brace = set_exception[*brace][c]; //detection si { ou ? ou $
	return (valid_tab[*brace][c]);
}

/*
** expand : extract the expand var and replace the remaining of
** 	the to_tokenize string
*/

int expand(char **to_tokenize, int *i, int *context, t_env *env)
{
	int j;
	int brace; // va servir aussi si ? et $
	char *var_name;

	j = 1;
	brace = 0;
	while (to_tokenize[0][(*i) + j] && is_valid_expand_char(&brace, to_tokenize[0][*i + j], j)) // && brace != 3))
		j++;
	//if (brace == 2 || brace == 3) //parce qu'on s est arrete avant
	//	j++;
	var_name = ft_substr(*to_tokenize, *(i), j); // recup la name var verifier erreurs ici
	printf("ici %s \n", var_name);
	if (j == 1)
		return (2);
	if (j > 1)
		*to_tokenize = ft_str_replace(*to_tokenize, *i, j - 1, env);
	handle_quoted_context(context, i, *to_tokenize);
	return (handle_error_inside(var_name, brace));
}
