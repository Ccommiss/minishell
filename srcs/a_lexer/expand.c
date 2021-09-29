
#include "minishell.h"

char *ft_str_replace(char *str, int start, int len, t_env *env)
{
	char *var_name;
	char *new_str;
	char *value;
	char *tmp;

	var_name = ft_substr(str, start + 1, len); // recup la name var
	while (env && ft_strncmp(var_name, env->key, ft_strlen(env->key) + 1) != 0) 
	{
		printf ("%s %s\n", env->key, env->value );
		env = env->next;
	}
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
	return (new_str);
}