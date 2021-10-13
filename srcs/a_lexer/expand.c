
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
	if (env == NULL)
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


// PROBLEME : si mauvais subsitution de var, aucun moyen de le dire au token pour le moment 
// idee ; creer un retour pour expand et si expand -1, on fait pas le token 
int	expand(char **to_tokenize, int *i, int *context, t_env *env)
{
	int j;
	int brace;

	j = 0;
	brace = 0;
	while (to_tokenize[0][*i+j] && (ft_isalnum(to_tokenize[0][*i+j]) || to_tokenize[0][*i+j] == '$' || to_tokenize[0][*i+j] == '{'
		|| to_tokenize[0][*i+j] == '}')) 
	{
		printf (" test : %c - %c \n", to_tokenize[0][*i+j], to_tokenize[0][*i+j+1]);
		if (j == 1 && to_tokenize[0][*i+j] == '{')
			brace = 1;
		if ((j > 0 && to_tokenize[0][*i+j] == '$') || (j > 1 && to_tokenize[0][*i+j] == '{'))
			break ; //si on a deux var collees
		j++;
		if (to_tokenize[0][*i+j] == '}' )
		{
			if (brace == 1) 
				brace = 2;
			break;
		}
	}
	if (brace == 1){
		printf ("BRACE ERROR OU MAUVAISE SUBSTITUITION");
		return (-1);
	}
	if (brace == 2)
		j++;
	if (j > 1) // si on a plus que juste le $
		*to_tokenize = ft_str_replace(*to_tokenize, *i, j - 1, env);
	printf ("to_tokenize = %s \n", *to_tokenize );
	handle_quoted_context(context, i, *to_tokenize); // TEST
	return (0);
}
